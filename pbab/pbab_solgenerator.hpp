#ifndef PBAB_SOLGENERATOR_HPP
#define PBAB_SOLGENERATOR_HPP

#include <vector>

namespace pbab {

/**
 * Class for solutions generation from some solution.
 * Generate childs from soltion.
 */
template <typename T>
class SolGenerator {
public:
    /**
     * Generate childs of the current solution.
     *
     * @return vector of new solutions
     */
    virtual std::vector<T> generate_childs(const T&) const = 0;
};

} // namespace pbab

#endif /* PBAB_SOLGENERATOR_HPP */
