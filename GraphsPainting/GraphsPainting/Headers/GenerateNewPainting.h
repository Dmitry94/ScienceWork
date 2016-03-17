#ifndef GENERATE_NEW_PAINTING_H
#define GENERATE_NEW_PAINTING_H

#include <list>

#include "Graph.h"
#include "GraphPaintingStructures.h"
#include "Operation.h"


class GenerateNewPainting : public Operation<PartialPaint>
{
public:
	GenerateNewPainting(const Graph &sourceGraph);
	std::vector<PartialPaint> getNextGeneration(const PartialPaint &cr_curPainting) const override;
	static bool isRightPainting(const PartialPaint &painting, const Graph &graph);
private:
	const Graph *m_pGraph;
};

#endif /* GENERATE_NEW_PAINTING_H */
