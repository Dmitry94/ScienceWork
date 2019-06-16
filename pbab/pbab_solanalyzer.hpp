#ifndef PBAB_SOLANALYZER_HPP
#define PBAB_SOLANALYZER_HPP


namespace pbab {

/**
 * Template abstract class for Solution Analyzer object.
 *
 * Solution Analyzer object parametrized with type T, which means
 * type of BAB(branch and bounds method) solution.
 *
 * Solution Analyzer object says, is current solution perspective or
 * needs to be excluded for further investigation
 * (its childs won't be investigated)
 *
 */
template <typename T>
class SolAnalyzer {
public:
    /** Virtual desctructor */
    virtual ~SolAnalyzer();

    /**
     * Analyzes current solution and says: is it perspective to
     * consume its childs.
     *
     * @return perspective flag
     */
    virtual bool is_solution_perspective(const T&) const = 0;
};

} // namespace pbab

#endif /* PBAB_SOLANALYZER_HPP */
