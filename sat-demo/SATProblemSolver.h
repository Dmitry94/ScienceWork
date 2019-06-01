#ifndef SAT_PROBLEM_SOLVER_H
#define SAT_PROBLEM_SOLVER_H

#include <unordered_set>

#include "SAT_Structures.h"
#include "SATSubstitutionGenerator.h"
#include "SATAmputation.h"
#include "Expression.h"
#include "../TreeAlgsParallization/TreeProblemSolver.h"

class SATProblemSolver : public TreeProblemSolver<PartialSubstitution, SubstitutionRating>
{
public:
	SATProblemSolver(const Expression &expr) : TreeProblemSolver<PartialSubstitution, SubstitutionRating>() 
	{
		m_Expression = &expr;
		std::unordered_set<std::string> uniqueVars;
		m_UniqueVars = calcCountOfUniqueVariables(&expr, uniqueVars);
		initOperations();
	}
protected:
	bool isAnswer(const PartialSubstitution &substitution) const override
	{
		// если с данной подстановкой формула истина, значит мы нашли решение
		Logic3 expressionValue = applySubstitution(m_Expression, substitution);
		return expressionValue == TRUE ? true : false;
	}
	bool isBetterAnswer(const PartialSubstitution &oldAnswer, const PartialSubstitution &newAnswer) const override
	{
		// если old пустой, значит решения нет, значит найденный ответ лучше
		return oldAnswer.size() == 0;
	}
	PartialSubstitution getObviousAnswer() const override
	{
		PartialSubstitution subs;
		return subs;
	}
	void recalcAmputations() override
	{
		Amputation<PartialSubstitution> *amputation = new SATAmputation(m_Answer);
		if (m_Amputations != nullptr)
		{
			std::for_each(m_Amputations->begin(), m_Amputations->end(), [](Amputation<PartialSubstitution> *amp) { delete amp; });
			m_Amputations->clear();
			m_Amputations->push_back(amputation);
		}
		else
		{
			m_Amputations = new std::list<Amputation<PartialSubstitution> *>(1, amputation);
		}
	}
	void initOperations() override
	{
		Operation<PartialSubstitution> *operation = new SATSubstitutionGenerator();
		m_Operations = new std::vector<Operation<PartialSubstitution> *>(1, operation);
	}
private:
	const Expression *m_Expression;
	unsigned m_UniqueVars;
};

#endif /* SAT_PROBLEM_SOLVER_H */
