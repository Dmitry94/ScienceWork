#ifndef TREE_PROBLEM_SOLVER_H
#define TREE_PROBLEM_SOLVER_H

#define CONTAINER_FOR_QUEUE std::deque

#include <queue>
#include <stack>
#include <thread>
#include <algorithm>
#include <mutex> 
#include<omp.h>

#include "ISolver.h"
#include "Operation.h"
#include "Node.h"
#include "Amputation.h"

template <typename T, class Compare = less<typename CONTAINER_FOR_QUEUE<Node<T> *>::value_type>>
class TreeProblemSolver : public ISolver<T>
{
public:
	TreeProblemSolver()
	{
		m_UsingAlgorithm = &TreeProblemSolver::DFS;
	}
	~TreeProblemSolver()
	{
		std::for_each(m_Operations->begin(), m_Operations->end(), [](Operation<T> *op) { delete op; });
		delete m_Operations;

		std::for_each(m_Amputations->begin(), m_Amputations->end(), [](Amputation<T> *amp) { delete amp; });
		delete m_Amputations;
	}
	T getAnswer(const T &startValue)
	{
		Node<T> *startNode = new Node<T>(startValue, nullptr);
		m_Answer = getObviousAnswer();
		recalcAmputations();
		DFS(startNode);
		return m_Answer;
	}
	T getAnswerParallel(const T &startValue, int countOfThreads = 1) override
	{
		// init, all memory will be deleted in algo
		m_Answer = getObviousAnswer();
		recalcAmputations();
		Node<T> *startNode = new Node<T>(startValue, nullptr);
		int countOfStartNodes = countOfThreads;

		/********************** START A* WHILE NOT ENOUGH NODES FOR PARALLEL **********************/
		// init
		priority_queue<Node <T>*, CONTAINER_FOR_QUEUE<Node <T>*>, Compare> nodesQueue;
		nodesQueue.push(startNode);
		int queueSize = 1;
		// main loop
		while (queueSize < countOfStartNodes)
		{
			// if finished before collect enough
			if (nodesQueue.empty())
				return m_Answer;

			// get next
			Node <T> *tmp = nodesQueue.top();
			nodesQueue.pop();
			queueSize--;

			// if current node need to be cut
			if (isAnyAmputation(tmp->value))
			{
				delete tmp;
				continue;
			}

			// check is it answer and skip. if it's then check is it better and assign if it is
			if (isAnswer(tmp->value))
			{
				if (isBetterAnswer(m_Answer, tmp->value))
				{
					m_Answer = tmp->value;
					recalcAmputations();
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

		///********************* IF WE COLLECT ENOUGH FOR PARALLEL ALGO, THEN START IT *********************/
		//vector <thread> threads(countOfThreads);
		//// for each node run its thread
		//while (!nodesQueue.empty())
		//{
		//	// if we have queueSize > countOfThreads, we have to run tasks by groups with size = countOfThreads
		//	if (queueSize > countOfThreads)
		//	{
		//		for (int i = 0; i < countOfThreads; i++)
		//		{
		//			// get node
		//			Node<T> *tmp = nodesQueue.top();
		//			nodesQueue.pop();
		//			queueSize--;
		//			// run thread
		//			threads[i] = thread(m_UsingAlgorithm, this, tmp);
		//		}
		//	}
		//	else
		//	{
		//		for (int i = 0; i < queueSize; i++)
		//		{
		//			// get node
		//			Node<T> *tmp = nodesQueue.top();
		//			nodesQueue.pop();
		//			// run thread
		//			threads[i] = thread(m_UsingAlgorithm, this, tmp);
		//		}
		//	}
		//	for_each(threads.begin(), threads.end(), [](thread &t) { if (t.joinable()) t.join(); });
		//}
		//
		//threads.clear();
		double *times = new double[countOfThreads];
		for (int i = 0; i < countOfThreads; i++)
			times[i] = 0.0;
		#pragma omp parallel num_threads(countOfThreads)
		{
			#pragma omp for schedule(dynamic, 1) nowait
			for (int i = 0; i < queueSize; i++)
			{
				Node<T> *tmp;
				#pragma omp critical
				{
					tmp = nodesQueue.top();
					nodesQueue.pop();
				}
				double st = omp_get_wtime();
				DFS(tmp);
				double end = omp_get_wtime();
				times[omp_get_thread_num()] += (end - st);
			}
		}

		//std::cout << std::endl;
		//for (int i = 0; i < countOfThreads; i++)
		//{
		//	times[i] /= 12.0;
		//	std::cout << times[i] << std::endl;
		//}
		//std::getchar();

		// return result
		return m_Answer;
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
	void DFS(Node<T> *start)
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
			//m_Mutex.lock();
			bool f = false;
			#pragma omp critical 
			{
				if (isAnyAmputation(tmp->value))
				{
					delete tmp;
					f = true;
					//m_Mutex.unlock();
					//continue;
				}
				//m_Mutex.unlock();
			}
			if (f)
				continue;

			// check is it answer then skip and it it's better than curAnswer, then lock and assign
			if (isAnswer(tmp->value))
			{
				//m_Mutex.lock();
				#pragma omp critical
				{
					if (isBetterAnswer(m_Answer, tmp->value))
					{
						m_Answer = tmp->value;
						recalcAmputations();
					}
					//m_Mutex.unlock();
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
	}
	bool isAnyAmputation(const T &current) const
	{
		for (typename std::list<Amputation<T> *>::const_iterator cIt = m_Amputations->cbegin(); cIt != m_Amputations->cend(); cIt++)
		{
			if ((*cIt)->isNeedToAmputate(current))
				return true;
		}
		return false;
	}

	/******************************** Virtual methods ********************************/
	virtual bool isBetterAnswer(const T &, const T &) const = 0;
	virtual T getObviousAnswer() const = 0;
	virtual void recalcAmputations() = 0;
	virtual void initOperations() = 0;

	/******************************** MEMBERS ********************************/
	std::vector<Operation<T> *> *m_Operations;
	std::list<Amputation<T> *> *m_Amputations;
	std::mutex m_Mutex;

	typedef void(TreeProblemSolver::*Algo)(Node<T> *);
	Algo m_UsingAlgorithm;

	// when we change answer, we have to recalculate amputations
	T m_Answer;
};

#endif /* TREE_PROBLEM_SOLVER_H */
