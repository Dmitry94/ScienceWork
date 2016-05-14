#include "../../Headers/GraphPainting/GraphPaintingGenerator.h"
#include "../../Headers/TreeAlgsParallization/Graph.h"
#include "../../Cpp/Graph.cpp"

#include <list>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;


GraphPaintingGenerator::GraphPaintingGenerator(const Graph & sourceGraph)
{
	m_pGraph = &sourceGraph;
}

std::vector<PartialPaint> GraphPaintingGenerator::getNextGeneration(const PartialPaint & cr_curPainting) const
{
	{
		// calc what vertex is next
		PartialPaint::const_iterator iter = --cr_curPainting.end();
		int whoIsNext = (*iter).first + 1;
		int maxColor = cr_curPainting.ColorsCount;

		// reserve memory for items
		std::vector<PartialPaint> answer;
		answer.reserve(iter->second);


		// get adjacent vertexes and check their colors to know what colors are free
		const std::list<int> adjacentVertexes = m_pGraph->getAllAdjancentVertexes(whoIsNext);
		// colors that are not free
		std::unordered_set<int> candidatesSet;
		for (std::list<int>::const_iterator it = adjacentVertexes.cbegin(); it != adjacentVertexes.end(); it++)
		{
			int curNeighbor = (*it);
			for (PartialPaint::const_iterator it2 = cr_curPainting.cbegin(); it2 != cr_curPainting.end(); it2++)
			{
				int curVert = (*it2).first;
				if (curVert == curNeighbor)
				{
					int curColor = (*it2).second;
					candidatesSet.insert(curColor);
				}
			}
		}

		// get set of partialPainting by painting cur vertex in one of the free color
		for (int color = 0; color < maxColor; color++)
		{
			if (candidatesSet.find(color) != candidatesSet.end())
				continue;
			PartialPaint tmp = cr_curPainting;
			tmp.push_back(VertexColorPair(whoIsNext, color));
			answer.push_back(tmp);
		}

		// if couldnt paint in color, we add new color
		if (answer.size() == 0)
		{
			PartialPaint tmp = cr_curPainting;
			tmp.push_back(VertexColorPair(whoIsNext, maxColor));
			tmp.ColorsCount = maxColor + 1;
			answer.push_back(tmp);
		}

		return answer;
	}
}

bool GraphPaintingGenerator::isRightPainting(const PartialPaint & painting, const Graph & graph)
{
	{
		for (PartialPaint::const_iterator it = painting.cbegin(); it != painting.cend(); it++)
		{
			std::list<int> curAdjacent = graph.getAllAdjancentVertexes(it->first);
			int curColor = it->second;
			for (std::list<int>::const_iterator it2 = curAdjacent.cbegin(); it2 != curAdjacent.cend(); it2++)
			{
				PartialPaint::const_iterator findElem = find_if(painting.cbegin(), painting.cend(),
					[it2](VertexColorPair elem) { return elem.first == *it2; });
				if (findElem->second == curColor)
					return false;
			}
		}
		return true;
	}
}
