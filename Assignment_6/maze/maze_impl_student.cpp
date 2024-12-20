#include "maze.h"
#include "bfs.h"
#include "dfs.h"

/** \brief Return the valid next states from a given state */
std::vector<State> ProblemDefinition::validStates(const State &state) const {
    std::vector<State> valid_neighbors;
    
    // Define possible movements (up, right, down, left)
    const std::vector<std::pair<int, int>> moves = {
        {-1, 0},  // up
        {1, 0},   // down
        {0, -1},  // left
        {0, 1}    // right
    };
    
    // Add diagonal moves if allowed
    const std::vector<std::pair<int, int>> diagonal_moves = {
        {-1, -1}, // up-left
        {-1, 1},  // up-right
        {1, -1},  // down-left
        {1, 1}    // down-right
    };
    
    // Check non-diagonal moves
    for (const auto& move : moves) {
        State next_state(state.x + move.first, state.y + move.second);
        if (isStateValid(next_state)) {
            valid_neighbors.push_back(next_state);
        }
    }
    
    // Check diagonal moves if allowed
    if (allow_diagonal_) {
        for (const auto& move : diagonal_moves) {
            State next_state(state.x + move.first, state.y + move.second);
            if (isStateValid(next_state)) {
                valid_neighbors.push_back(next_state);
            }
        }
    }
    
    return valid_neighbors;
}

/** \brief Given a node, extract the path from it to the root */
void TreeSearch::extractPath(NodePtr node) {
    // Initialize empty solution path
    path_.clear();
    
    // Handle invalid node case
    if (!node) {
        return;
    }
    
    // Back-track from goal to start in the tree to get path
    NodePtr current = node;
    while (current) {
        // Record each state in the path
        visited_.push_back(current->state);
        path_.insert(path_.begin(), current->state);
        
        // Move to parent node
        current = current->parent;
    }
}

/** \brief Solve the planning problem. Override TreeSearch::solve() */
bool BFS::solve() {
    // Validate start and goal states
    if (!pdef_.isStateValid(pdef_.startState()) || 
        !pdef_.isStateValid(pdef_.goalState())) {
        return false;
    }

    // Check if start is goal
    auto start = pdef_.startState();
    if (pdef_.isGoal(start)) {
        return true;
    }

    // Initialize root node
    NodePtr root = std::make_shared<Node>();
    root->state = pdef_.startState();
    root->parent = nullptr;
    root->cost_to_come = 0;
    
    // Add root to open list and visited set
    OpenList.push(root);
    visitedNodes.insert(root);

    NodePtr solution = nullptr;
    
    // Main BFS loop
    while (!OpenList.empty()) {
        // Choose node to expand (FIFO for BFS)
        NodePtr current = OpenList.front();
        OpenList.pop();
        
        // Check if current node is goal
        if (pdef_.isGoal(current->state)) {
            solution = current;
            break;
        }
        
        // Expand current node
        std::vector<State> neighbors = pdef_.validStates(current->state);
        for (const auto& nextState : neighbors) {
            // Create new node
            NodePtr newNode = std::make_shared<Node>();
            newNode->state = nextState;
            newNode->parent = current;
            newNode->cost_to_come = current->cost_to_come + 1;
            
            // Add node if not visited
            if (visitedNodes.find(newNode) == visitedNodes.end()) {
                visitedNodes.insert(newNode);
                OpenList.push(newNode);
                visited_.push_back(nextState);
            }
        }
    }

    // If solution found, extract path
    if (solution) {
        extractPath(solution);
        return true;
    }
    
    return false;
}

/** \brief add node to the tree */
bool BFS::addNode(const NodePtr &node) {
    // Check if node is valid
    if (!node) {
        return false;
    }
    
    // Check if state is valid
    if (!pdef_.isStateValid(node->state)) {
        return false;
    }
    
    // Check if node has already been visited
    if (visitedNodes.find(node) != visitedNodes.end()) {
        return false;
    }
    
    // Add node to visited set and open list
    visitedNodes.insert(node);
    OpenList.push(node);
    visited_.push_back(node->state);
    
    return true;
}

bool DFS::solve() {
    if (!pdef_.isStateValid(pdef_.startState()) || 
        !pdef_.isStateValid(pdef_.goalState())) {
        return false;
    }

    auto start = pdef_.startState();
    if (pdef_.isGoal(start)) {
        return true;
    }

    NodePtr root = std::make_shared<Node>();
    root->state = pdef_.startState();
    root->parent = nullptr;
    root->cost_to_come = 0;
    
    openList.push(root);
    visitedNodes.insert(root);
    visited_.push_back(root->state);

    NodePtr solution = nullptr;
    
    while (!openList.empty()) {
        NodePtr current = openList.top();
        openList.pop();
        
        if (pdef_.isGoal(current->state)) {
            solution = current;
            break;
        }
        
        std::vector<State> neighbors = pdef_.validStates(current->state);
        for (const auto& nextState : neighbors) {
            NodePtr newNode = std::make_shared<Node>();
            newNode->state = nextState;
            newNode->parent = current;
            newNode->cost_to_come = current->cost_to_come + 1;
            
            if (addNode(newNode)) {
                maxDepth = std::max(maxDepth, static_cast<size_t>(newNode->cost_to_come));
            }
        }
    }

    if (solution) {
        extractPath(solution);
        return true;
    }
    return false;
}

// Implementation of DFS::addNode()
bool DFS::addNode(const NodePtr& node) {
    if (!node || !pdef_.isStateValid(node->state)) {
        return false;
    }
    
    for (const auto& visited : visitedNodes) {
        if (visited->state.x == node->state.x && 
            visited->state.y == node->state.y) {
            return false;
        }
    }
    
    visitedNodes.insert(node);
    openList.push(node);
    visited_.push_back(node->state);
    return true;
}