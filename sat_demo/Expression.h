#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include <unordered_set>
#include "SAT_Structures.h"
#include "Logic3.h"

class Expression {
public:
	virtual std::string toString() = 0;
};

class Constant : public Expression {
public:
	bool value;
	Constant(bool value);
	std::string toString() override;
};

class Variable : public Expression {
public:
	std::string name;
	Variable(const std::string &name);
	std::string toString() override;
};

class Conjunction : public Expression {
public:
	Expression *left, *right;
	Conjunction(Expression *left, Expression *right);
	std::string toString() override;
	~Conjunction();
};

class Disjunction : public Expression {
public:
	Expression *left, *right;
	Disjunction(Expression *left, Expression *right);
	std::string toString() override;
	~Disjunction();
};

class Negative : public Expression {
public:
	Expression *expr;
	Negative(Expression *expr);
	std::string toString() override;
	~Negative();
};

void freeExpression(Expression *exp);
Expression* generateRandomExpression(unsigned countOfVariables, unsigned maxCountOneVariableAppearances);
Logic3 applySubstitution(const Expression *exp, const PartialSubstitution &substitution);
unsigned calcCountOfUniqueVariables(const Expression *expr, std::unordered_set<std::string> &usedVars);

#endif EXPRESSION_H