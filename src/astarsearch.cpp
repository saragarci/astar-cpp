#include "astarsearch.hpp"

#include <iostream>
#include <typeinfo>

namespace {
    template<typename T>
    void print_queue(T q) { // NB: pass by value so the print uses a copy
        while (!q.empty()) {
            std::cout << q.top().getState().getName() << ' ';
            q.pop();
        }
        std::cout << '\n';
    }
}

namespace astar {

/** 
 * Constructor of AstarSearch
 */
AstarSearch::AstarSearch(Map & map, std::array<int, 2> start, std::array<int, 2> goal, std::array<std::array<int, 2>, 4> actions)
     : map{map},
       actions{actions}
{
    map.setStart(start);
    map.setGoal(goal);
}

/** 
 * Retrieve the shortest path by iterating from the solution to
 * until the goal using the parent pointers.
 * Then call printSolution() on the map object to show the solution
 * on graphics.
 */
void AstarSearch::showShortestPath()
{
    // Check if BFS returned the solution node or failure
    auto result = BestFirstSearch();
    if (!result.has_value()){
        std::cerr << "Failure\n";
        return;
    }

    result->getState()->setIsSolution(true);

    auto c_parent = result->getParent();
    while (c_parent != nullptr) {
        const Node n_parent = reached.at(c_parent->getName());
        n_parent.getState()->setIsSolution(true);
        c_parent = n_parent.getParent();
    }
    setSolutionFound(true);
}

/**
 * Implementation of best-first search algorithm
 */
std::optional<Node> AstarSearch::BestFirstSearch()
{
    auto * start = map.getStart();
    assert(start);
    
    map.print();
    SDL_Delay(1000);
    
    Node n = Node{start, nullptr, actionCost(start), computeH(start)};
    frontier.push(n);
    reached.insert({start->getName(), n});
    start->setIsReached(true);
    while (!frontier.empty()) {
        const Node node = frontier.top();
        frontier.pop();
        if (isGoal(node))
            return node;

        for (Node child : expandNode(node)) {
            Cell * s = child.getState();
            auto search = reached.find(s->getName());
            if (search == reached.end()) {
                reached.insert({s->getName(), child});
                s->setIsReached(true);
                frontier.push(child);
            } else if (child.getG() < reached.at(s->getName()).getG()) {
                reached.at(s->getName()) = child;
                frontier.push(child);
            }
            SDL_Delay(10);
            map.print();
        }
    }
    return {};
}

/*
 * Check if a node state corresponds to the goal state
 */
bool AstarSearch::isGoal(Node node)
{
    return node.getState()->getIsGoal();
}

/*
 * Compute all the childs descending from a node as a result of
 * applying the set of actions available in the problem
 */
std::vector<Node> AstarSearch::expandNode(Node node)
{
    std::vector<Node> childs{};
    
    Cell * parent = node.getState();
    for (auto action : actions) {
        auto * child = applyAction(parent, action);
        if (child != nullptr) {
            int g = node.getG() + actionCost(child);
            childs.emplace_back(Node{child, parent, g, computeH(child)});
        }
    }

    return childs;
}

/*
 * Get the new cell position after applying an action
 */
Cell * AstarSearch::applyAction(Cell * s, std::array<int, 2> action)
{
    int x = s->getXCoord() + action[0];
    int y = s->getYCoord() + action[1];

    auto * cell = map.getCellAtCoordinates(x, y);
    bool is_valid_cell = cell != nullptr && cell->getValue() != -1;
    return is_valid_cell ? cell : nullptr;
}

/*
 * Return the cost of going to a cell
 */
int AstarSearch::actionCost(Cell * cell)
{
    return cell->getValue();
}

/*
 * Compute the manhattan distance
 */
int AstarSearch::computeH(Cell * state)
{
    return abs(map.getGoal()->getXCoord() - state->getXCoord()) + abs(map.getGoal()->getYCoord() - state->getYCoord());
}

void AstarSearch::setSolutionFound(bool isSolved)
{
    solutionFound = isSolved;
}

bool AstarSearch::getSolutionFound()
{
    return solutionFound;
}

}
