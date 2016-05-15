#include <string>
#include "../../Headers/SAT/SATSubstitutionGenerator.h"

using namespace std;

vector<PartialSubstitution> SATSubstitutionGenerator::getNextGeneration(const PartialSubstitution &currentSubstitution) const
{
	vector<PartialSubstitution> answer;
	// if all variables has value
	if (currentSubstitution.size() == currentSubstitution.countOfVariables)
		return answer;

	unsigned index = currentSubstitution.size();
	PartialSubstitution subs1 = currentSubstitution;
	PartialSubstitution subs2 = currentSubstitution;
	subs1.insert(pair<string, bool>("x" + to_string(index), true));
	subs2.insert(pair<string, bool>("x" + to_string(index), false));

	answer.push_back(subs1);
	answer.push_back(subs2);

	return answer;
}