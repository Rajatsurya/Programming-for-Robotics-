#pragma once
#include "maze.h"
// other includes
// --- Your code here
#include <stack>
#include <unordered_set>
#include <memory>
// ---
struct NodePtrHash {
    std::size_t operator()(const NodePtr& node) const {
        return std::hash<int>()(node->state.x) ^ (std::hash<int>()(node->state.y) << 1);
    }
};

struct NodePtrEqual {
    bool operator()(const NodePtr& lhs, const NodePtr& rhs) const {
        return lhs->state.x == rhs->state.x && lhs->state.y == rhs->state.y;
    }
};

/** \brief Depth First Search solver */
class DFS : public TreeSearch {
   public:
    DFS();

    /** \brief Solve the planning problem. Override TreeSearch::solve() */
    bool solve();

    /** \brief add node to the tree */
    bool addNode(const NodePtr& node);

private:
    std::stack<NodePtr> openList;
    std::unordered_set<NodePtr, NodePtrHash, NodePtrEqual> visitedNodes;
    size_t maxDepth = 0;
};
using DFSPtr = std::shared_ptr<DFS>;