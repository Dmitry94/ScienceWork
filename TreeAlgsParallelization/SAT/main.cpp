#include <iostream>
#include <time.h>

#include "../Source/Headers/SAT/Expression.h"
#include "../Source/Headers/SAT/SAT_Structures.h"

using namespace std;

int main()
{
	srand((unsigned)(time(NULL)));

	for (int i = 0; i < 10; i++)
	{
		Expression *ex = generateRandomExpression(i + 2, 2);
		PartialSubstitution subs;
		for (int j = 0; j <= i; j++)
		{
			subs.insert(pair<string, bool>("x" + to_string(j), 1));
		}
		cout << ex->toString() << endl;
		cout << applySubstitution(ex, subs) << endl;
		freeExpression(ex);
	}

	system("pause");
	return 0;
}