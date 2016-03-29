#include <iostream>
#include <time.h>
#include <vector>

#include "../Headers/Node.h"

#include "../Headers/Graph/Graph.h"
#include "../Headers/Graph/GraphPainting/GraphPainting.h"

#include "../Headers/HTML/HTML_Logger.h"

using namespace std;

inline void printStat(const PartialPaint &partialPaint, const Graph &graph, double time, bool isParallel)
{
	bool isGood = GenerateNewPainting::isRightPainting(partialPaint, graph);
	cout << "For count = " + to_string(partialPaint.size()) << ", ";
	cout << (isGood ? "Everything is Ok" : "Bad answer") << (isParallel ? " in parallel" : "") << endl;
	cout << "Time = ";
	cout << time << endl;
	cout << "Count of colors = " << to_string(partialPaint.ColorsCount) << endl << endl;
}

int main() {
	srand((unsigned)(time(NULL)));

	list<string> headers = { "Count of Vertexes", "Count of Edges", "One Thread Time", "100 thread Time", "Result"};
	HTML_Logger log(headers);
	int minVertexCount = 20;
	int maxVertexCount = 55;
	int threadsCount = 24;

	cout << "Calculating..." << endl;

	for (int count = minVertexCount; count < maxVertexCount; count++)
	{
		cout << "Current graph has " << count << " vertexes..." << endl;

		Graph graph = Graph::generateRandomGraph(count);
		unsigned start_time, end_time;
		double SimpleTime = -1, ParallelTime = -1;

		PartialPaint start(1, VertexColorPair(0, 0));
		GraphPainting solver(graph);
		PartialPaint answer, parallelAnswer;
		bool isGood;

		// Simple code
		if (count <= 30)
		{
			start_time = clock();
				answer = solver.getAnswer(start);
			end_time = clock();

			SimpleTime = (double)(end_time - start_time) / CLOCKS_PER_SEC;
			isGood = GenerateNewPainting::isRightPainting(answer, graph);
			if (!isGood)
			{
				cout << "ERROR" << endl;
				return 1;
			}
		}

		

		// Parallel code
		start_time = clock();
			parallelAnswer = solver.getAnswer(start, threadsCount);
		end_time = clock();
		
		// calc time
		ParallelTime = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		
		// check
		isGood = GenerateNewPainting::isRightPainting(parallelAnswer, graph);
		if (!isGood)
		{
			cout << "ERROR" << endl;
			return 1;
		}

		// update logfile
		list<string> curResults = { to_string(graph.getSize()), to_string(graph.getCountOfEdges())
			, to_string(SimpleTime) + " sec" ,to_string(ParallelTime) + " sec"
			, to_string(parallelAnswer.ColorsCount) + " colors"};

		log.addLogLine(curResults);
		log.createFile("@../../res.html");
	}

	std::system("pause");
	return 0;
}