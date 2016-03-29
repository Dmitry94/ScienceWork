#ifndef GRAPH_PAINTING_AMPUTATION_H
#define GRAPH_PAINTING_AMPUTATION_H

#include "../../Amputation.h"
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

#endif /* GRAPH_PAINTING_AMPUTATION_H */
