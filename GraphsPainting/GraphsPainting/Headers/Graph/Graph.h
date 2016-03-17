#ifndef GRAPH_H
#define GRAPH_H

#define BINARY_IN_MODE (std::ios::binary | std::ios::in)
#define BINARY_OUT_MODE (std::ios::binary | std::ios::out)
#define TEXT_IN_MODE std::ios::in
#define TEXT_OUT_MODE std::ios::out

#include <list>
#include <string>
#include <fstream>
#include <vector>

class Graph {
public:
	Graph() {}
	Graph(const std::string &rFileName, std::ios_base::openmode mode);
	/// Writing Graph into file, mode = {BINARY_IN_MODE | BINARY_OUT_MODE | TEXT_IN_MODE | TEXT_OUT_MODE}
	void writeIntoFile(const std::string &rFileName, std::ios_base::openmode mode) const;
	int getSize() const
	{
		return m_Graph.size();
	}
	int getCountOfEdges() const
	{
		int answer = 0;
		for (std::vector<std::list<int>>::const_iterator cIt = m_Graph.cbegin(); cIt != m_Graph.cend(); cIt++)
			answer += cIt->size();
		return answer / 2;
	}
	std::list<int> getAllAdjancentVertexes(int vertex) const;

	/**************** STATIC *******************/
	static Graph generateRandomGraph(int countOfVertexes);
private:
	typedef std::vector<std::list<int>> GraphType;
	GraphType m_Graph;
};

#endif /* GRAPH_H */
