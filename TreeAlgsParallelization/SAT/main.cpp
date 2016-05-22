#include <iostream>
#include <time.h>

#include "../Source/Headers/SAT/Expression.h"

#include "../Source/Headers/SAT/SAT_Structures.h"
#include "../Source/Headers/SAT/SATProblemSolver.h"

#include "../Source/Headers/HTML/HTML_Logger.h"
using namespace std;

int main()
{
	srand((unsigned)(time(NULL)));

	int minVarsCount = 10;
	int maxVarsCount = 40;
	int threadsCount = 18;
	double countOfPatterns = 3.0;

	list<string> headers = { "Count of unique vars", "Max count of each var apperiance", "One Thread Time", to_string(threadsCount) + " thread Time", "Performance" };
	HTML_Logger log(headers);

	cout << "Calculating..." << endl;

	for (int count = minVarsCount; count <= maxVarsCount; count += 2)
	{
		cout << "Current expression has " << count << " unique variables...";
		double oneThreadTimeAverage = 0, manyThreadTimeAverage = 0;
		unsigned maxCountOfEachVarApperiance = (rand() % 15) + 3;

		for (int j = 0; j < countOfPatterns; j++)
		{
			cout << "    " << (j + 1) << "...";
			Expression *curEx = generateRandomExpression(count, maxCountOfEachVarApperiance);
			long long start_time, end_time;
			bool isGood;

			PartialSubstitution start(count);
			SATProblemSolver solver(*curEx);
			PartialSubstitution answer, parallelAnswer;

			// Simple code
			start_time = clock();
			answer = solver.getAnswer(start);
			end_time = clock();
			oneThreadTimeAverage += (double)(end_time - start_time) / CLOCKS_PER_SEC;

			isGood = SATSubstitutionGenerator::isAnswer(*curEx, answer);
			if (!isGood)
			{
				cout << "ERROR" << endl;
				return 1;
			}

			// Parallel code
			start_time = clock();
			parallelAnswer = solver.getAnswerParallel(start, threadsCount);
			end_time = clock();
			manyThreadTimeAverage += (double)(end_time - start_time) / CLOCKS_PER_SEC;

			isGood = SATSubstitutionGenerator::isAnswer(*curEx, parallelAnswer);
			if (!isGood)
			{
				cout << "ERROR" << endl;
				return 1;
			}

			freeExpression(curEx);
		}
		cout << endl;

		oneThreadTimeAverage /= countOfPatterns;
		manyThreadTimeAverage /= countOfPatterns;

		// update logfile
		list<string> curResults = { to_string(count), to_string(maxCountOfEachVarApperiance)
			, to_string(oneThreadTimeAverage) + " sec" ,to_string(manyThreadTimeAverage) + " sec"
			, to_string(oneThreadTimeAverage / manyThreadTimeAverage) };

		log.addLogLine(curResults);
		log.createFile("@../../SAT_Results.html");
	}

	system("pause");
	return 0;
}