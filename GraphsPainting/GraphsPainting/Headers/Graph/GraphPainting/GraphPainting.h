#ifndef GRAPH_PAINTING_H
#define GRAPH_PAINTING_H

#include "../GraphProblem.h"
#include "GraphPaintingStructures.h"
#include "GenerateNewPainting.h"

class GraphPainting : public GraphProblem<PartialPaint, PaintingRating>
{
public:
	GraphPainting(const Graph &graph)
		: GraphProblem<PartialPaint, PaintingRating>(graph, std::vector<Operation<PartialPaint> *>())
	{
		Operation<PartialPaint> *operation = new GenerateNewPainting(graph);
		m_Operations = new std::vector<Operation<PartialPaint> *>(1, operation);
	}
	~GraphPainting()
	{
		delete m_Operations;
	}
protected:
	bool isTimeToExit(const Node<PartialPaint> &node) const override
	{
		return node.value.size() == m_pGraph->getSize();
	}
};

#endif /* GRAPH_PAINTING_H */