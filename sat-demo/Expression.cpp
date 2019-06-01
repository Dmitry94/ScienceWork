#include <string>
#include <unordered_set>

#include "../../Headers/SAT/Expression.h"
#include "../../Headers/SAT/Logic3.h"

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

Logic3 applySubstitution(const Expression *exp, const PartialSubstitution &substitution)
{
	const Disjunction *dis;
	const Conjunction *con;
	const Negative *neg;
	const Variable *var;
	const Constant *constant;
	Logic3 answer;
	if ((dis = dynamic_cast<const Disjunction *>(exp)) != nullptr)
	{
		Logic3 fstOperand = applySubstitution(dis->left, substitution);
		Logic3 sndOperand = applySubstitution(dis->right, substitution);
		answer = Logic3_Operations::getDisjunction(fstOperand, sndOperand);
	}
	else if ((con = dynamic_cast<const Conjunction *>(exp)) != nullptr)
	{
		Logic3 fstOperand = applySubstitution(con->left, substitution);
		Logic3 sndOperand = applySubstitution(con->right, substitution);
		answer = Logic3_Operations::getConjuction(fstOperand, sndOperand);
	}
	else if ((neg = dynamic_cast<const Negative*>(exp)) != nullptr)
	{
		Logic3 operand = applySubstitution(neg->expr, substitution);
		answer = Logic3_Operations::getNegative(operand);
	}
	else if((var = dynamic_cast<const Variable*>(exp)) != nullptr)
	{
		if (substitution.find(var->name) != substitution.end())
			answer = Logic3(substitution.at(var->name));
		else
			answer = Logic3();
	}
	else if ((constant = dynamic_cast<const Constant*>(exp)) != nullptr)
	{
		answer = Logic3(constant->value);
	}
	return answer;
}

std::ostream& operator<<(std::ostream& os, const Logic3 value)
{
	if (value == TRUE)
		os << "TRUE";
	else if (value == FALSE)
		os << "FALSE";
	else
		os << "UNDEFINED";
	return os;
}

unsigned calcCountOfUniqueVariables(const Expression *expr, unordered_set<string> &usedVars)
{
	const Disjunction *dis;
	const Conjunction *con;
	const Negative *neg;
	const Variable *var;
	const Constant *constant;
	unsigned count = 0;
	if ((dis = dynamic_cast<const Disjunction *>(expr)) != nullptr)
	{
		count += calcCountOfUniqueVariables(dis->left, usedVars) + calcCountOfUniqueVariables(dis->right, usedVars);
	}
	else if ((con = dynamic_cast<const Conjunction *>(expr)) != nullptr)
	{
		count += calcCountOfUniqueVariables(con->left, usedVars) + calcCountOfUniqueVariables(con->right, usedVars);
	}
	else if ((neg = dynamic_cast<const Negative*>(expr)) != nullptr)
	{
		count += calcCountOfUniqueVariables(neg->expr, usedVars);
	}
	else if ((var = dynamic_cast<const Variable*>(expr)) != nullptr)
	{
		if (usedVars.find(var->name) == usedVars.end())
		{
			count++;
			usedVars.insert(var->name);
		}
	}

	return count;
}