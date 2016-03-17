#ifndef Operation_H
#define Operation_H

#include <vector>

template <typename T>
class Operation {
public:
	Operation() {}
	virtual std::vector<T> getNextGeneration(const T&) const = 0;
	~Operation() {}
};

#endif /* Operation_H */
