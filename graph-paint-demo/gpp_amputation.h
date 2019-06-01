#ifndef GPP_AMPUTATION_H
#define GPP_AMPUTATION_H

#include "../TreeAlgsParallization/Amputation.h"
#include "GraphPaintingStructures.h"

class GraphPaintingAmputation : public Amputation<PartialPaint>
{
public:
	GraphPaintingAmputation(const PartialPaint &curAnswer) 
	{
		m_CurAnswer = curAnswer;
	}
	bool isNeedToAmputate(const PartialPaint& painting) const override
	{
		return painting.ColorsCount >= m_CurAnswer.ColorsCount;
	}

private:
	PartialPaint m_CurAnswer;
};

#endif /* GPP_AMPUTATION_H */
