#ifndef NP_SOLVER_H
#define NP_SOLVER_H

template <typename T>
class IProblem
{
public:
	virtual T getAnswerParallel(const T&, int) = 0;
	virtual T getAnswer(const T&) = 0;
	virtual ~IProblem() {}
protected:
	virtual bool isAnswer(const T &) const = 0;
};

#endif /* NP_SOLVER_H */