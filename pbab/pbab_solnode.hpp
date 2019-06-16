#ifndef PBAB_SOLNODE_HPP
#define PBAB_SOLNODE_HPP

#include <memory>

namespace pbab {

/**
 * Struct of node of solutiuon search tree.
 */
template <typename T>
struct SolNode {
    /** depth level of current node inside solution tree, 0 means root level */
    int level;

    /** link to the parent node */
    const std::weak_ptr<SolNode> parent;

    /** solution of this node */
    T value;

    /** Initialization */
    SolNode(T val, const std::weak_ptr<SolNode> parent, int level = 0) {
        value = val;
        this->parent = parent;
        this->level = level;
    }
};

}

#endif /* PBAB_SOLNODE_HPP */
