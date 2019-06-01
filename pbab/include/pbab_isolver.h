#ifndef ISOLVER_H
#define ISOLVER_H

template <typename T>
class ISolver
{
public:
	virtual T getAnswerParallel(const T&, int) = 0;
	virtual T getAnswer(const T&) = 0;
	virtual ~ISolver() {}
protected:
	virtual bool isAnswer(const T &) const = 0;
};

#endif /* ISOLVER_H */