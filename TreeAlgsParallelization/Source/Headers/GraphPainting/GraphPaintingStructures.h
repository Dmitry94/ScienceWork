#ifndef GRAPH_PAINTING_STRUCTURES
#define GRAPH_PAINTING_STRUCTURES

#include <list>

#include "../TreeAlgsParallization/Node.h"

typedef std::pair<int, int> VertexColorPair;

struct PartialPaint : public std::list<VertexColorPair>
{
	int ColorsCount = 1;
	PartialPaint(int count, VertexColorPair elem) : std::list<VertexColorPair>(count, elem) {}
	PartialPaint() : std::list<VertexColorPair>() {}
};

class PaintingRating
{
public:
	bool operator()(Node<PartialPaint> const*p1, Node<PartialPaint> const*p2) const
	{
		return p1->value.size() / (double)p1->value.ColorsCount > p2->value.size() / (double)p2->value.ColorsCount;
	}
};

#endif /* GRAPH_PAINTING_STRUCTURES */