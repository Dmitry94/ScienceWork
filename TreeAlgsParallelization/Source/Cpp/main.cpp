#include <iostream>
#include <time.h>
#include <vector>

#include "../Headers/TreeAlgsParallization/Node.h"
#include "../Headers/TreeAlgsParallization/Graph.h"

#include "../Headers/GraphPainting/GraphPaintingProblemSolver.h"

#include "../Headers/HTML/HTML_Logger.h"

using namespace std;

inline void printStat(const PartialPaint &partialPaint, const Graph &graph, double time, bool isParallel)
{
	bool isGood = GraphPaintingGenerator::isRightPainting(partialPaint, graph);
	cout << "For count = " + to_string(partialPaint.size()) << ", ";
	cout << (isGood ? "Everything is Ok" : "Bad answer") << (isParallel ? " in parallel" : "") << endl;
	cout << "Time = ";
	cout << time << endl;
	cout << "Count of colors = " << to_string(partialPaint.ColorsCount) << endl << endl;
}

int main() {
	srand((unsigned)(time(NULL)));

	int minVertexCount = 30;
	int maxVertexCount = 70;
	int threadsCount = 18;
	double countOfPatterns = 3.0;

	list<string> headers = { "Count of Vertexes", "Count of Edges", "One Thread Time", to_string(threadsCount) + " thread Time", "Performance" };
	HTML_Logger log(headers);

	cout << "Calculating..." << endl;

	for (int count = minVertexCount; count <= maxVertexCount; count += 2)
	{
		cout << "Current graph has " << count << " vertexes...";
		double oneThreadTimeAverage = 0, manyThreadTimeAverage = 0;
		unsigned edgesCountAverage = 0;

		for (int j = 0; j < countOfPatterns; j++)
		{
			cout << "    " << (j + 1) << "...";
			Graph graph = Graph::generateRandomGraph(count);
			edgesCountAverage += graph.getCountOfEdges();
			long long start_time, end_time;

			PartialPaint start(1, VertexColorPair(0, 0));
			GraphPaintingProblemSolver solver(graph);
			PartialPaint answer, parallelAnswer;
			bool isGood;

			// Simple code
			start_time = clock();
			answer = solver.getAnswer(start);
			int colorsCount = answer.ColorsCount;
			end_time = clock();

			oneThreadTimeAverage += (double)(end_time - start_time) / CLOCKS_PER_SEC;

			isGood = GraphPaintingGenerator::isRightPainting(answer, graph);
			if (!isGood)
			{
				cout << "ERROR" << endl;
				return 1;
			}



			// Parallel code
			start_time = clock();
			parallelAnswer = solver.getAnswerParallel(start, threadsCount);
			end_time = clock();

			// calc time
			manyThreadTimeAverage += (double)(end_time - start_time) / CLOCKS_PER_SEC;

			// check
			isGood = GraphPaintingGenerator::isRightPainting(parallelAnswer, graph) && colorsCount == answer.ColorsCount;
			if (!isGood)
			{
				cout << "ERROR" << endl;
				return 1;
			}
		}
		cout << endl;

		oneThreadTimeAverage /= countOfPatterns;
		manyThreadTimeAverage /= countOfPatterns;
		edgesCountAverage /= countOfPatterns;

		// update logfile
		list<string> curResults = { to_string(count), to_string(edgesCountAverage)
			, to_string(oneThreadTimeAverage) + " sec" ,to_string(manyThreadTimeAverage) + " sec"
			, to_string(oneThreadTimeAverage / manyThreadTimeAverage)};

		log.addLogLine(curResults);
		log.createFile("@../../res.html");
	}

	std::system("pause");
	return 0;
}