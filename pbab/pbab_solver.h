#ifndef PBAB_SOLVER_H
#define PBAB_SOLVER_H


namespace pbab {

/**
 * Abstract class of task solver.
 * It's assumed, that all logic will be inside derrived classes.
 * But each solver can give solution.
 *
 * T - type of solution.
 * Solution - some state of task, which fits to all specified conditions.
 *
 * For example:
 *  T - configuration of some variables satisfaction
 *  some state of T is solution, if formula with this configuration is equal to
 *  desirable out and it is the best.
 *
 */
template <typename T>
class Solver
{
public:
    /**
     * Run searching solution.
     *
     * @return best solution configuration
     */
    virtual T get_solution(const T&) = 0;

    /** Each solver should say, if some state is solution. */
    virtual bool is_solution(const T&) const = 0;

    /** Virtual destructor. */
    virtual ~Solver() = 0;
};

} // namespace pbab

#endif /* PBAB_SOLVER_H */
