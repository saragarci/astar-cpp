#include "astarsearch.hpp"

#include <iostream>
#include <typeinfo>

namespace {
    // private functions

    template<typename T>
    void print_queue(T q) { // NB: pass by value so the print uses a copy
        while(!q.empty()) {
            std::cout << q.top().getState().getName() << ' ';
            q.pop();
        }
        std::cout << '\n';
    }

}

namespace astar {

AstarSearch::AstarSearch(Map & map, std::array<int, 2> start, std::array<int, 2> goal, std::array<std::array<int, 2>, 4> actions)
     : map{map},
       actions{actions}
{
    map.setStart(start);
    map.setGoal(goal);
}

void AstarSearch::showShortestPath()
{
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

    map.printSolution();
}

/** 
 * Implementation of best-first search algorithm
 */
std::optional<Node> AstarSearch::BestFirstSearch()
{
    auto * start = map.getStart();
    assert(start);

    Node n = Node{start, nullptr, actionCost(start), computeH(start)};
    frontier.push(n);
    reached.insert({start->getName(), n});
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
                frontier.push(child);
            } else if (child.getG() < reached.at(s->getName()).getG()) {
                reached.at(s->getName()) = child;
                frontier.push(child);
            }
        }
    }
    return {};
}

bool AstarSearch::isGoal(Node node)
{
    return node.getState()->getIsGoal();
}

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

Cell * AstarSearch::applyAction(Cell * s, std::array<int, 2> action)
{
    int x = s->getXCoord() + action[0];
    int y = s->getYCoord() + action[1];

    auto * cell = map.getCellAtCoordinates(x, y);
    if (cell == nullptr)
        return {};

    return cell->getValue() != -1 ? cell : nullptr;
}

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

}
