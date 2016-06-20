#ifndef GRAPH_PAINTING_GENERATOR_H
#define GRAPH_PAINTING_GENERATOR_H

#include <list>

#include "GraphPaintingStructures.h"
#include "Graph.h"
#include "../TreeAlgsParallization/Operation.h"


class GraphPaintingGenerator : public Operation<PartialPaint>
{
public:
	GraphPaintingGenerator(const Graph &sourceGraph);
	std::vector<PartialPaint> getNextGeneration(const PartialPaint &cr_curPainting) const override;
	static bool isRightPainting(const PartialPaint &painting, const Graph &graph);
private:
	const Graph *m_pGraph;
};

#endif /* GRAPH_PAINTING_GENERATOR_H */
