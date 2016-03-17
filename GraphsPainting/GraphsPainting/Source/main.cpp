#include <iostream>
#include <time.h>
#include <vector>

#include "../Headers/Graph/Graph.h"
#include "../Headers/Graph/GraphPainting/GraphPainting.h"

#include "../Headers/Node.h"


#include "../Headers/HTML/HTML_Logger.h"

using namespace std;

inline void printStat(const PartialPaint &partialPaint, const Graph &graph, double time, bool isParallel)
{
	bool isGood = GenerateNewPainting::isRightPainting(partialPaint, graph);
	cout << "For count = " + to_string(partialPaint.size()) << ", ";
	cout << (isGood ? "Everything is Ok" : "Bad answer") << (isParallel ? " in parallel" : "") << endl;
	cout << "Time = ";
	cout << time << endl;
	cout << "Count of colors = " << to_string(partialPaint.MaxColor) << endl << endl;
}

int main() {
	srand((unsigned)(time(NULL)));
	unsigned start_time, end_time;
	double AStarTime, ParallelAStarTime;


	list<string> headers = { "Count of Vertexes", "Count of Edges", "AStar Time", "Parallel AStar Time", "AStar Result", "Parallel AStar Result" };
	HTML_Logger log(headers);

	cout << "Calculating..." << endl;

	for (int count = 5; count < 41; count++)
	{
		Graph graph = Graph::generateRandomGraph(count);
		
		PartialPaint start(1, VertexColorPair(0, 0));
		GraphPainting solver(graph);
		Node<PartialPaint> *startNode;

		// Simple code
		startNode = new Node<PartialPaint>(start, nullptr);
		start_time = clock();
		PartialPaint answer = solver.getAnswer(startNode);
		end_time = clock();
		AStarTime = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		//printStat(answer, graph, AStarTime, false);
		delete startNode;

		// Parallel code
		startNode = new Node<PartialPaint>(start, nullptr);
		start_time = clock();
		PartialPaint parallelAnswer = solver.getAnswerParallel(startNode);
		end_time = clock();
		ParallelAStarTime = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		//printStat(parallelAnswer, graph, ParallelAStarTime, true);
		delete startNode;

		list<string> curResults = { to_string(graph.getSize()), to_string(graph.getCountOfEdges())
			, to_string(AStarTime) + " sec" ,to_string(ParallelAStarTime) + " sec"
			, to_string(answer.MaxColor) + " colors", to_string(parallelAnswer.MaxColor) + " colors" };

		log.addLogLine(curResults);
	}

	log.createFile("@../../res.html");

	std::system("pause");
	return 0;
}