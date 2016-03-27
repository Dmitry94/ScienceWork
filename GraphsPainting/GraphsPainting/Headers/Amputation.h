#ifndef AMPUTATION_H
#define AMPUTATION_H

template <typename T>
class Amputation
{
public:
	~Amputation() {}
	virtual bool isNeedToAmputate(const T&) const = 0;
};

#endif /* AMPUTATION_H */
