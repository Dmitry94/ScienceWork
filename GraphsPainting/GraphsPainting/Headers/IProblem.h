#ifndef NP_SOLVER_H
#define NP_SOLVER_H

template <typename T>
class IProblem
{
public:
	virtual T getAnswer(const T&, int) = 0;
	virtual ~IProblem() {}
protected:
	virtual bool isAnswer(const T &) const = 0;
};

#endif /* NP_SOLVER_H */