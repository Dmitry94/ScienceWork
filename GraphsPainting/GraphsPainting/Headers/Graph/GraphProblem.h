#ifndef GRAPH_PROBLEM_H
#define GRAPH_PROBLEM_H

#define CONTAINER_FOR_QUEUE std::vector

#include <queue>
#include <thread>

#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/shared_lock_guard.hpp>
#include <boost/thread/condition_variable.hpp>

#include "../IProblem.h"
#include "../Operation.h"
#include "Graph.h"

template <typename T, class Compare = less<typename std::vector<Node<T> *>::value_type>>
class GraphProblem : public IProblem<T>
{
public:
	GraphProblem(const Graph &graph, const std::vector<Operation<T> *> &operations)
	{
		m_pGraph = &graph;
		m_Operations = &operations;
	}

	T getAnswer(Node<T> *startNode) override
	{
		return AStar(startNode);
	}

	T getAnswerParallel(Node<T> *startNode) override
	{
		// start A* while not enough nodes
		priority_queue<Node <T>*, CONTAINER_FOR_QUEUE<Node <T>*>, Compare> nodesQueue;
		nodesQueue.push(startNode);
		int queueSize = 1;
		while (queueSize < MAX_THREADS)
		{
			Node <T> *tmp = nodesQueue.top();
			nodesQueue.pop();
			queueSize--;

			if (isTimeToExit(*tmp))
				return tmp->value;

			for (typename vector<Operation<T> *>::const_iterator it = m_Operations->cbegin(); it != m_Operations->cend(); it++)
			{
				vector<T> values = (*it)->getNextGeneration(tmp->value);
				for (typename vector<T>::const_iterator it = values.cbegin(); it != values.cend(); it++)
				{
					Node <T> *new_Node = new Node <T>(*it, tmp, tmp->level + 1);
					nodesQueue.push(new_Node);
					tmp->sons.push_back(new_Node);
					queueSize++;
				}
			}
		}

		// if nodes >= MAX_THREADS then start parallel
		vector <thread> threads;
		while(!nodesQueue.empty())
		{
			Node<T> *tmp = nodesQueue.top();
			nodesQueue.pop();
			for (int i = 0; i < MAX_THREADS; i++)
			{
				threads.push_back(thread(&GraphProblem::AStarParallel, this, tmp));
			}
		}

		for_each(threads.begin(), threads.end(), mem_fun_ref(&thread::join));

		return parallelAnswer;
	}
protected:
	/******************************** METHODS ********************************/
	T AStar(Node <T> *start) const
	{
		priority_queue<Node <T>*, CONTAINER_FOR_QUEUE<Node <T>*>, Compare> nodesQueue;
		nodesQueue.push(start);
		while (!nodesQueue.empty())
		{
			Node <T> *tmp = nodesQueue.top();
			nodesQueue.pop();

			if (isTimeToExit(*tmp))
			{
				return tmp->value;
			}

			for (typename vector<Operation<T> *>::const_iterator it = m_Operations->cbegin(); it != m_Operations->cend(); it++)
			{
				vector<T> values = (*it)->getNextGeneration(tmp->value);
				for (typename vector<T>::const_iterator it = values.cbegin(); it != values.cend(); it++)
				{
					Node <T> *new_Node = new Node <T>(*it, tmp, tmp->level + 1);
					nodesQueue.push(new_Node);
					tmp->sons.push_back(new_Node);
				}
			}
		}
	}

	void AStarParallel(Node <T> *start)
	{
		priority_queue<Node <T>*, CONTAINER_FOR_QUEUE<Node <T>*>, Compare> nodesQueue;
		nodesQueue.push(start);

		while (!nodesQueue.empty())
		{
			boost::upgrade_lock<boost::shared_mutex> lock(m_SharedMutex);
			Node <T> *tmp = nodesQueue.top();
			nodesQueue.pop();

			if (parallelAnswer.size() != 0)
				return;

			if (isTimeToExit(*tmp))
			{
				boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);
				parallelAnswer = tmp->value;
				return;
			}

			for (typename vector<Operation<T> *>::const_iterator it = m_Operations->cbegin(); it != m_Operations->cend(); it++)
			{
				vector<T> values = (*it)->getNextGeneration(tmp->value);
				for (typename vector<T>::const_iterator it = values.cbegin(); it != values.cend(); it++)
				{
					Node <T> *new_Node = new Node <T>(*it, tmp, tmp->level + 1);
					nodesQueue.push(new_Node);
					tmp->sons.push_back(new_Node);
				}
			}
		}
	}

	/******************************** MEMBERS ********************************/
	const int MAX_THREADS = 6;

	const Graph *m_pGraph;
	const std::vector<Operation<T> *> *m_Operations;
	boost::shared_mutex m_SharedMutex;

	T parallelAnswer;

};

#endif /* GRAPH_PROBLEM_H */
