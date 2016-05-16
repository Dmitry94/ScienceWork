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
	}
protected:
	bool isAnswer(const PartialSubstitution &substitution) const override
	{
		//
		return false;
	}
	bool isBetterAnswer(const PartialSubstitution &oldAnswer, const PartialSubstitution &newAnswer) const override
	{
		return true;
	}
	PartialSubstitution getObviousAnswer() const override
	{
		PartialSubstitution subs;
		for (int j = 0; j <= m_UniqueVars; j++)
		{
			subs.insert(std::pair<std::string, bool>("x" + std::to_string(j), 0));
		}
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
