#include <iostream>
#include <time.h>
#include <vector>

#include "../Headers/Graph.h"
#include "../Headers/Node.h"
#include "../Headers/Operation.h"
#include "../Headers/GenerateNewPainting.h"
#include "../Headers/GraphPainting.h"

#include "../Headers/HTML_Logger/HTML.h"
#include "../Headers/HTML_Logger/HTML_Table.h"
using namespace std;

inline void printStat(const PartialPaint &partialPaint, const Graph &graph, unsigned time, bool isParallel)
{
	bool isGood = GenerateNewPainting::isRightPainting(partialPaint, graph);
	cout << "For count = " + to_string(partialPaint.size()) << ", ";
	cout << (isGood ? "Everything is Ok" : "Bad answer") << (isParallel ? " in parallel" : "") << endl;
	cout << "Time = ";
	cout << (double)time/ CLOCKS_PER_SEC << endl;
	cout << "Count of colors = " << to_string(partialPaint.MaxColor) << endl << endl;
}

int main() {
	srand((unsigned)(time(NULL)));
	unsigned start_time, end_time, search_time;


	HTML_MetaTag tag("charset=\"utf - 8\"");
	list<HTML_MetaTag> tags(1, tag);
	HTML_Title title("Results");
	HTML_Head head(tags, title);

	HTML_Caption c("Table");
	HTML_Td t1("32"); HTML_Td t2("33"); HTML_Td t3("34");
	HTML_Tr tr;
	tr.addTd(t1); tr.addTd(t2); tr.addTd(t3);
	HTML_Table tab(c);
	tab.addTr(tr);
	list<const HTML_Tag *> Btags;
	HTML_Tag *Btag = &tab;
	Btags.push_back(Btag);
	HTML_Body body(Btags);

	HTML h(head, body);
	cout << h.toString() << endl;

	//for (int count = 15; count < 100; count++)
	//{
	//	Graph graph = Graph::generateRandomGraph(count);
	//	
	//	PartialPaint start(1, VertexColorPair(0, 0));
	//	GraphPainting solver(graph);
	//	Node<PartialPaint> *startNode;

	//	// Simple code
	//	startNode = new Node<PartialPaint>(start, nullptr);
	//	start_time = clock();
	//	PartialPaint answer = solver.getAnswer(startNode);
	//	end_time = clock();
	//	search_time = end_time - start_time;
	//	printStat(answer, graph, search_time, false);
	//	delete startNode;

	//	// Parallel code
	//	startNode = new Node<PartialPaint>(start, nullptr);
	//	start_time = clock();
	//	PartialPaint parallelAnswer = solver.getAnswerParallel(startNode);
	//	end_time = clock();
	//	search_time = end_time - start_time;
	//	printStat(parallelAnswer, graph, search_time, true);
	//	delete startNode;
	//}

	std::system("pause");
	return 0;
}