#ifndef NP_SOLVER_H
#define NP_SOLVER_H

#include "Node.h"

template <typename T>
class IProblem
{
public:
	virtual T getAnswer(Node<T> *) = 0;
	virtual T getAnswerParallel(Node<T> *) = 0;
	virtual ~IProblem() {}
protected:
	virtual bool isTimeToExit(const Node<T> &node) const = 0;
};

#endif /* NP_SOLVER_H */