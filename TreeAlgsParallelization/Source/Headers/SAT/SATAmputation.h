#ifndef SAT_AMPUTATION_H
#define SAT_AMPUTATION_H

#include "../TreeAlgsParallization/Amputation.h"
#include "SAT_Structures.h"

class SATAmputation : public Amputation<PartialSubstitution>
{
public:
	SATAmputation(const PartialSubstitution &curSubstitution)
	{
		m_Substitution = curSubstitution;
	}
	bool isNeedToAmputate(const PartialSubstitution& painting) const override
	{
		// TODO return is answer already exists
		return true;
	}

private:
	PartialSubstitution m_Substitution;
};

#endif /* SAT_AMPUTATION_H */