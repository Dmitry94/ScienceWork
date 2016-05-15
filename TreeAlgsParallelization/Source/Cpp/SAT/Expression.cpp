#include <string>
#include <unordered_set>

#include "../../Headers/SAT/Expression.h"

using namespace std;


// Constant
Constant::Constant(bool value)
{
	this->value = value;
}
string Constant::toString() {
	return value ? "1" : "0";
}



// Variable
Variable::Variable(const std::string & name)
{
	this->name = name;
}
string Variable::toString() {
	return name;
}


// Conjunction
Conjunction::Conjunction(Expression * left, Expression * right)
{
	this->left = left;
	this->right = right;
}
std::string Conjunction::toString()
{
	return left->toString() + " & " + right->toString();
}
Conjunction::~Conjunction()
{}


// Disjunction
Disjunction::Disjunction(Expression * left, Expression * right)
{
	this->left = left;
	this->right = right;
}
std::string Disjunction::toString()
{
	return "(" + left->toString() + " | " + right->toString() + ")";
}
Disjunction::~Disjunction()
{}


// Negative
Negative::Negative(Expression *expr)
{
	this->expr = expr;
}
std::string Negative::toString()
{
	if (dynamic_cast<Variable*>(expr))
		return "~" + expr->toString();
	else
		return "~(" + expr->toString() + ")";
}
Negative::~Negative() {}

void freeExpression(Expression *expr) {
	Disjunction *dis;
	Conjunction *con;
	Negative *neg;
	if ((dis = dynamic_cast<Disjunction *>(expr)) != nullptr) {
		freeExpression(dis->left);
		freeExpression(dis->right);
	}
	else if ((con = dynamic_cast<Conjunction *>(expr)) != nullptr) {
		freeExpression(con->left);
		freeExpression(con->right);
	}
	else if ((neg = dynamic_cast<Negative*>(expr)) != nullptr) {
		freeExpression(neg->expr);
	}
	delete expr;
}

Expression* generateRandomExpression(unsigned countOfVariables, unsigned maxCountOneVariableAppearances)
{
	if (countOfVariables < 2 && maxCountOneVariableAppearances < 1)
		return nullptr;
	Expression *answer = new Variable("x0");
	unsigned curCountOfVars = 1;
	unordered_set<unsigned> usedVars;
	usedVars.insert(0);
	while (curCountOfVars < countOfVariables)
	{
		unsigned randNum;
		// random: var or const?
		randNum = 1; //rand() % 2;
		Expression *cur;
		if (randNum == 0)
		{
			randNum = rand() % 2;
			cur = new Constant(randNum);
		}
		else
		{
			// which var we will use?
			unsigned index = rand() % countOfVariables;
			if (usedVars.find(index) == usedVars.end())
			{
				curCountOfVars++;
				usedVars.insert(index);
			}
			cur = new Variable("x" + to_string(index));
			// random: is neg?
			randNum = rand() % 2;
			if (randNum == 1)
				cur = new Negative(cur);
		}

		// rand: conj or disj?
		randNum = rand() % 2;
		if (randNum == 1)
			answer = new Conjunction(answer, cur);
		else
			answer = new Disjunction(answer, cur);
	}

	return answer;
}

bool applySubstitution(Expression *exp, const PartialSubstitution &substitution)
{
	Disjunction *dis;
	Conjunction *con;
	Negative *neg;
	Variable *var;
	Constant *constant;
	// -1 --- undefined
	// 0 --- false
	// 1 --- true
	int answer;
	if ((dis = dynamic_cast<Disjunction *>(exp)) != nullptr)
	{
		answer = applySubstitution(dis->left, substitution) || applySubstitution(dis->right, substitution);
	}
	else if ((con = dynamic_cast<Conjunction *>(exp)) != nullptr)
	{
		answer = applySubstitution(con->left, substitution) && applySubstitution(con->right, substitution);
	}
	else if ((neg = dynamic_cast<Negative*>(exp)) != nullptr)
	{
		int subVal = applySubstitution(neg->expr, substitution);
		if (subVal == -1)
			return -1;
		else
			answer = !subVal;
	}
	else if((var = dynamic_cast<Variable*>(exp)) != nullptr)
	{
		if (substitution.find(var->name) != substitution.end())
			answer = substitution.at(var->name);
		else
			answer = -1;
	}
	else if ((constant = dynamic_cast<Constant*>(exp)) != nullptr)
	{
		answer = constant->value;
	}
	return answer;
}