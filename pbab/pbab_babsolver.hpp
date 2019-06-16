#ifndef PBAB_BABSOLVER_HPP
#define PBAB_BABSOLVER_HPP

#include "pbab_solver.hpp"

namespace pbab {

/**
 * Abstract class of solver which is based on branch and bound method.
 */
class BABSolver : public Solver {
protected:
    /**
     * Get the simpliest solution.
     * @return some solution, which may be usefull in the start.
     */
    virtual T get_trivial_answer() const = 0;

    /**
     * Sometimes in process of searching best solution
     * it is necessary to recalculate solution analyzers.
     * In derrived classes it can be empty.
     */
    virtual void recalc_solanalyzers() = 0;

};

}

#endif // PBAB_BABSOLVER_HPP
