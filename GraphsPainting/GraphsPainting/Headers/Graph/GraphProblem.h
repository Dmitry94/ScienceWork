#ifndef GRAPH_PROBLEM_H
#define GRAPH_PROBLEM_H

#define CONTAINER_FOR_QUEUE std::deque

#include <queue>
#include <stack>
#include <thread>
#include <algorithm>
#include <mutex> 

#include "../IProblem.h"
#include "../Operation.h"
#include "../Node.h"
#include "../Amputation.h"

#include "Graph.h"

template <typename T, class Compare = less<typename std::vector<Node<T> *>::value_type>>
class GraphProblem : public IProblem<T>
{
public:
	GraphProblem(const Graph &graph)
	{
		m_pGraph = &graph;
		m_UsingAlgorithm = &GraphProblem::DFS;
	}
	~GraphProblem()
	{
		std::for_each(m_Operations->begin(), m_Operations->end(), [](Operation<T> *op) { delete op; });
		delete m_Operations;

		//std::for_each(m_Amputations->begin(), m_Amputations->end(), [](Amputation<T> *amp) { delete amp; });
		//delete m_Amputations;
	}
	T getAnswer(const T &startValue) override
	{
		Node<T> *startNode = new Node<T>(startValue, nullptr);
		m_Answers = std::vector<T>(1);
		T answer = getObviousAnswer();
		std::list<Amputation<T> *> amputations = recalcAmputations(answer);
		DFS(startNode, amputations, answer, 0);
		return m_Answers[0];
	}
	T getAnswerParallel(const T &startValue, int countOfThreads = 1) override
	{
		// count of nodes, which we will generate for DFS
		int countOfNodes = countOfThreads * 2;
		// answer, which we will be update
		T answer = getObviousAnswer();
		// init amputations
		std::list<Amputation<T> *> amputations = recalcAmputations(answer);
		// array for partial answers from threads
		m_Answers = std::vector<T>(countOfThreads);
		// init, all memory will be deleted in algo
		Node<T> *startNode = new Node<T>(startValue, nullptr);

		/********************** START A* WHILE NOT ENOUGH NODES FOR PARALLEL **********************/
		// init
		priority_queue<Node <T>*, CONTAINER_FOR_QUEUE<Node <T>*>, Compare> nodesQueue;
		nodesQueue.push(startNode);
		int queueSize = 1;
		// main loop, while not collect enough nodes or find min answer
		while (queueSize < countOfNodes)
		{
			// if finished before collect enough
			if (nodesQueue.empty())
				return answer;

			// get next
			Node <T> *tmp = nodesQueue.top();
			nodesQueue.pop();
			queueSize--;

			// if current node need to be cut
			if (isAnyAmputation(amputations, tmp->value))
			{
				delete tmp;
				continue;
			}

			// check is it answer and skip. if it's then check is it better and assign if it is
			if (isAnswer(tmp->value))
			{
				if (isBetterAnswer(answer, tmp->value))
				{
					answer = tmp->value;
					std::for_each(amputations.begin(), amputations.end(), [](Amputation<T> *amp) { delete amp; });
					amputations = recalcAmputations(answer);
				}
				delete tmp;
				continue;
			}

			// gen childs
			for (typename vector<Operation<T> *>::const_iterator it = m_Operations->cbegin(); it != m_Operations->cend(); it++)
			{
				// get childs
				vector<T> values = (*it)->getNextGeneration(tmp->value);
				for (typename vector<T>::const_iterator it = values.cbegin(); it != values.cend(); it++)
				{
					// push child and bind with current Node
					Node <T> *new_Node = new Node <T>(*it, tmp, tmp->level + 1);
					nodesQueue.push(new_Node);
					queueSize++;
				}
			}

			// free memory
			delete tmp;
		}

		/********************* IF WE COLLECT ENOUGH FOR PARALLEL ALGO, THEN START IT *********************/
		vector <thread> threads;
		// for each node run its thread
		while(!nodesQueue.empty())
		{
			// if we have queueSize > countOfThreads, we have to run tasks by groups with size = countOfThreads
			if (queueSize > countOfThreads)
			{
				for (int i = 0; i < countOfThreads; i++)
				{
					// get node
					Node<T> *tmp = nodesQueue.top();
					nodesQueue.pop();
					queueSize--;
					// run thread
					threads.push_back(thread(m_UsingAlgorithm, this, tmp, amputations, answer, i));
				}
			}
			else
			{
				while (!nodesQueue.empty())
				{
					int i = 0;
					// get node
					Node<T> *tmp = nodesQueue.top();
					nodesQueue.pop();
					// run thread
					threads.push_back(thread(m_UsingAlgorithm, this, tmp, amputations, answer, i++));
				}
			}

			// wait for all threads and clear
			for_each(threads.begin(), threads.end(), mem_fun_ref(&thread::join));
			threads.clear();
			// find the best answer from all
			for (int i = 0; i < m_Answers.size(); i++)
			{
				if (isBetterAnswer(answer, m_Answers[i]))
					answer = m_Answers[i];
			}
			amputations = recalcAmputations(answer);
		}

		// return result
		return answer;
	}
protected:
	/******************************** METHODS ********************************/
	void AStar(Node <T> *start)
	{
		// init
		priority_queue<Node <T>*, CONTAINER_FOR_QUEUE<Node <T>*>, Compare> nodesQueue;
		nodesQueue.push(start);
		// main loop
		while (!nodesQueue.empty())
		{
			// get next, shared lock for answer
			Node <T> *tmp = nodesQueue.top();
			nodesQueue.pop();

			m_Mutex.lock();
			// if current node need to be cut
			if (isAnyAmputation(tmp->value))
			{
				delete tmp;
				m_Mutex.unlock();
				continue;
			}
			m_Mutex.lock();

			// check is it answer then skip and it it's better than curAnswer, then lock and assign
			if (isAnswer(tmp->value))
			{
				m_Mutex.lock();
				if (isBetterAnswer(m_Answer, tmp->value))
				{
					m_Answer = tmp->value;
					recalcAmputations();
				}
				m_Mutex.unlock();
				delete tmp;
				continue;
			}

			// gen childs
			for (typename vector<Operation<T> *>::const_iterator it = m_Operations->cbegin(); it != m_Operations->cend(); it++)
			{
				// get childs
				vector<T> values = (*it)->getNextGeneration(tmp->value);
				for (typename vector<T>::const_iterator it = values.cbegin(); it != values.cend(); it++)
				{
					// push child in queue and bind it with current
					Node <T> *new_Node = new Node <T>(*it, tmp, tmp->level + 1);
					nodesQueue.push(new_Node);
				}
			}
			// free mem
			delete tmp;
		}
	}
	void DFS(Node<T> *start, std::list<Amputation<T> *> amputations, T curAnswer, int threadNum)
	{
		// init
		stack<Node <T>*, CONTAINER_FOR_QUEUE<Node <T>*>> nodesStack;
		nodesStack.push(start);
		// main loop
		while (!nodesStack.empty())
		{
			// get next, shared lock for answer
			Node <T> *tmp = nodesStack.top();
			nodesStack.pop();

			// if current node need to be cut
			if (isAnyAmputation(amputations, tmp->value))
			{
				delete tmp;
				continue;
			}

			// check is it answer then skip and it it's better than curAnswer, then lock and assign
			if (isAnswer(tmp->value))
			{
				if (isBetterAnswer(curAnswer, tmp->value))
				{
					curAnswer = tmp->value;
					//std::for_each(amputations.begin(), amputations.end(), [](Amputation<T> *amp) { delete amp; });
					amputations = recalcAmputations(curAnswer);
				}
				delete tmp;
				continue;
			}

			// gen childs
			for (typename vector<Operation<T> *>::const_iterator it = m_Operations->cbegin(); it != m_Operations->cend(); it++)
			{
				// get childs
				vector<T> values = (*it)->getNextGeneration(tmp->value);
				for (typename vector<T>::const_iterator it = values.cbegin(); it != values.cend(); it++)
				{
					// push child in queue and bind it with current
					Node <T> *new_Node = new Node <T>(*it, tmp, tmp->level + 1);
					nodesStack.push(new_Node);
				}
			}
			// free mem
			delete tmp;
		}
		m_Answers[threadNum] = curAnswer;
	}
	bool isAnyAmputation(const std::list<Amputation<T> *> &amputations, const T &current) const
	{
		for (typename std::list<Amputation<T> *>::const_iterator cIt = amputations.cbegin(); cIt != amputations.cend(); cIt++)
		{
			if ((*cIt)->isNeedToAmputate(current))
				return true;
		}
		return false;
	}
	
	/******************************** Virtual methods ********************************/
	virtual bool isBetterAnswer(const T &, const T &) const = 0;
	virtual T getObviousAnswer() const = 0;
	virtual std::list<Amputation<T> *> recalcAmputations(const T&) = 0;
	virtual void initOperations() = 0;

	/******************************** MEMBERS ********************************/
	const Graph *m_pGraph;
	std::vector<Operation<T> *> *m_Operations;
	//std::list<Amputation<T> *> *m_Amputations;
	std::mutex m_Mutex;

	typedef void(GraphProblem::*Algo)(Node<T> *, std::list<Amputation<T> *>, T, int);
	Algo m_UsingAlgorithm;
	std::vector<T> m_Answers;

	// when we change answer, we have to recalculate amputations
	//T m_Answer;
};

#endif /* GRAPH_PROBLEM_H */
