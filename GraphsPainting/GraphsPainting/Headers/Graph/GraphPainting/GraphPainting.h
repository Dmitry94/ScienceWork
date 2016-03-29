#ifndef GRAPH_PAINTING_H
#define GRAPH_PAINTING_H

#include "../GraphProblem.h"

#include "GraphPaintingStructures.h"
#include "GenerateNewPainting.h"

#include "GraphPaintingAmputation.h"

class GraphPainting : public GraphProblem<PartialPaint, PaintingRating>
{
public:
	GraphPainting(const Graph &graph)
		: GraphProblem<PartialPaint, PaintingRating>(graph)
	{
		initOperations();
		recalcAmputations();
	}
protected:
	bool isAnswer(const PartialPaint &value) const override
	{
		return value.size() == m_pGraph->getSize();
	}
	bool isBetterAnswer(const PartialPaint &oldAnswer, const PartialPaint &newAnswer) const override
	{
		return newAnswer.ColorsCount < oldAnswer.ColorsCount;
	}
	PartialPaint getObviousAnswer() const override
	{
		PartialPaint answer;
		// paint each vertex by its color and one more
		answer.ColorsCount = m_pGraph->getSize() + 1;
		return answer;
	}
	void recalcAmputations() override
	{
		Amputation<PartialPaint> *amputation = new GraphPaintingAmputation(m_Answer);

		if (m_Amputations != nullptr)
		{
			std::for_each(m_Amputations->begin(), m_Amputations->end(), [](Amputation<PartialPaint> *amp) { delete amp; });
			m_Amputations->clear();
			m_Amputations->push_back(amputation);
		}
		else
		{
			m_Amputations = new std::list<Amputation<PartialPaint> *>(1, amputation);
		}
	}
	void initOperations() override
	{
		Operation<PartialPaint> *operation = new GenerateNewPainting(*m_pGraph);
		m_Operations = new std::vector<Operation<PartialPaint> *>(1, operation);
	}
};

#endif /* GRAPH_PAINTING_H */