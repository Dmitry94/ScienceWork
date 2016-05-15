#include <iostream>
#include <time.h>

#include "../Source/Headers/SAT/Expression.h"

using namespace std;

int main()
{
	srand((unsigned)(time(NULL)));

	for (int i = 0; i < 10; i++)
	{
		Expression *ex = generateRandomExpression(i + 2, 2);
		cout << ex->toString() << endl;
		freeExpression(ex);
	}

	system("pause");
	return 0;
}