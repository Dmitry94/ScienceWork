#include "../Headers/TreeAlgsParallization/Graph.h"

Graph::Graph(const std::string & rFileName, std::ios_base::openmode mode)

{
	std::ifstream in(rFileName, mode);
	int count;
	if (mode == TEXT_IN_MODE)
	{
		in >> count;
		m_Graph.resize(count);
		for (typename GraphType::iterator it = m_Graph.begin(); it != m_Graph.end(); it++)
		{
			int currentCount;
			char delim;
			int currentItem;
			in >> currentCount;
			in >> delim;
			for (int j = 0; j < currentCount; j++)
			{
				in >> currentItem;
				it->push_back(currentItem);

				// add reverse edge
				m_Graph[currentItem].push_back(it - m_Graph.begin());
			}
		}
	}
	else if (mode == BINARY_IN_MODE)
	{
		in.read((char *)&count, sizeof(count));
		m_Graph.resize(count);
		for (typename GraphType::iterator it = m_Graph.begin(); it != m_Graph.end(); it++)
		{
			int currentCount;
			int currentItem;
			in.read((char *)&currentCount, sizeof(currentCount));
			for (int j = 0; j < currentCount; j++)
			{
				in.read((char *)&currentItem, sizeof(currentItem));
				it->push_back(currentItem);

				// add reverse edge
				m_Graph[currentItem].push_back(it - m_Graph.begin());
			}
		}
	}
	else
	{
		in.close();
		throw std::runtime_error("The filemode was wrong");
	}
	in.close();
}

void Graph::writeIntoFile(const std::string & rFileName, std::ios_base::openmode mode) const
{

	{
		std::ofstream out(rFileName, mode);
		int count = m_Graph.size();
		if (mode == TEXT_OUT_MODE)
		{
			out << std::to_string(count) << std::endl;
			for (typename GraphType::const_iterator it = m_Graph.cbegin(); it != m_Graph.cend(); it++)
			{
				out << std::to_string(it->size()) << ": ";
				for (typename std::list<int>::const_iterator itInside = it->cbegin(); itInside != it->cend(); itInside++)
				{
					out << std::to_string(*itInside) << " ";
				}
				out << std::endl;
			}
		}
		else if (mode == BINARY_OUT_MODE)
		{
			out.write((char *)&(count), sizeof(count));
			for (typename GraphType::const_iterator it = m_Graph.cbegin(); it != m_Graph.cend(); it++)
			{
				int currentSize = it->size();
				out.write((char *)&(currentSize), sizeof(currentSize));
				for (typename std::list<int>::const_iterator itInside = it->cbegin(); itInside != it->cend(); itInside++)
				{
					out.write((char *)&(*itInside), sizeof(*itInside));
				}
			}
		}
		else
		{
			out.close();
			throw std::runtime_error("The filemode was wrong");
		}
		out.close();
	}
}

std::list<int> Graph::getAllAdjancentVertexes(int vertex) const
{
	GraphType::const_iterator need = m_Graph.cbegin();
	for (int i = 0; i < vertex; i++)
		need++;
	return (*need);
}

Graph Graph::generateRandomGraph(int countOfVertexes)
{
	Graph resultGraph;
	GraphType *pData = &resultGraph.m_Graph;
	pData->resize(countOfVertexes);
	int curVertexIndex = 0;
	for (typename GraphType::iterator it = pData->begin(); it != pData->end(); it++)
	{
		int currentCountOfRelations = (rand() % (countOfVertexes / 2)) + 1;
		// while didnt generate all needed edges or vertex is alredy full
		while (currentCountOfRelations != 0 && it->size() < countOfVertexes - 1)
		{
			int currentChild = rand() % countOfVertexes;
			if (std::find(it->begin(), it->end(), currentChild) == it->end() && currentChild != curVertexIndex)
			{
				it->push_back(currentChild);
				currentCountOfRelations--;

				// add reverse edge
				(*pData)[currentChild].push_back(it - pData->begin());
			}
		}
		curVertexIndex++;
	}
	return resultGraph;
}
