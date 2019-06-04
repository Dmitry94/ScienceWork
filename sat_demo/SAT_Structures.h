#ifndef SAT_STRUCTURES_H
#define SAT_STRUCTURES_H

#include <unordered_map>
#include "../../Headers/TreeAlgsParallization/Node.h"

class PartialSubstitution : public std::unordered_map<std::string, bool>
{
public:
	PartialSubstitution(unsigned countOfVariables) : std::unordered_map<std::string, bool>()
	{
		this->countOfVariables = countOfVariables;
	}
	PartialSubstitution() : std::unordered_map<std::string, bool>() {}
	unsigned countOfVariables;
};

class SubstitutionRating
{
public:
	bool operator()(Node<PartialSubstitution> const*p1, Node<PartialSubstitution> const*p2) const
	{
		return p1->value.size() > p2->value.size();
	}
};

#endif /* SAT_STRUCTURES_H */