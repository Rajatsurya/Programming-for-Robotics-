#pragma once
#include "maze.h"
// other includes
// --- Your code here
#include<queue>
#include<unordered_set>
#include<memory>
// ---


/** \brief Breadth First Search solver */
class BFS : public TreeSearch {
   public:
    BFS();

    /** \brief Solve the planning problem. Override TreeSearch::solve() */
    bool solve();

    /** \brief add node to the tree */
    bool addNode(const NodePtr& node);

   private:
    // decide what data structure you need
    // --- Your code here
    std::queue<NodePtr> OpenList;//this holds the nodes
    std::unordered_set<NodePtr> visitedNodes;//this makes sure we donot revist nodes 
    size_t maxDepth = 0;// Optional: Track maximum depth explored (if needed)
    // ---
};
using BFSPtr = std::shared_ptr<BFS>;
