#ifndef SAT_SUBSTITUTION_GENERATOR_H
#define SAT_SUBSTITUTION_GENERATOR_H

#include "../TreeAlgsParallization/Operation.h"
#include "SAT_Structures.h"

class SATSubstitutionGenerator : public Operation<PartialSubstitution>
{
public:
	std::vector<PartialSubstitution> getNextGeneration(const PartialSubstitution &) const override;
};

#endif /* SAT_SUBSTITUTION_GENERATOR_H */