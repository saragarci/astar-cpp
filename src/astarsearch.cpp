#include "astarsearch.hpp"

#include <iostream>

namespace {
    // private functions
}

namespace astar {

AstarSearch::AstarSearch(Map & map, Cell & start, Cell & goal) : map{map}, start{start}, goal{goal}
{
    Cell up{0,1};
    Cell down{0,-1};
    Cell left{-1,0};
    Cell right{1,0};

    actions.emplace_back(up);
    actions.emplace_back(down);
    actions.emplace_back(left);
    actions.emplace_back(right);
}

void AstarSearch::showShortestPath()
{
    auto result = BestFirstSearch();
    if (!result.has_value()) std::cerr << "Failure\n";

    //std::vector<Cell> solution{};
    //solution.emplace_back(result.getState());

    /*Node n = result->getParent();
    while (n != nullptr) {
        auto state = n.getState();
        solution.emplace_back(state);
        n = n.getParent();
    }
    solution.emplace_back(n.getState());*/

    //map.printSolution(solution);
}

std::optional<Node> AstarSearch::BestFirstSearch()
{
    Node n = Node{start, {}, actionCost(start), computeH(start)};
    frontier.push(n);
    reached.insert({start.getName(), n});
    /*while (!frontier.empty()) {
        Node const & node = frontier.pop();
        if (isGoal(node))
            return node;

        for (Node child : expandNode(node)) {
            Cell s = child.getState();
            auto search = reached.find(s.getName());
            if (search != reached.end() || child.getG() < reached[s.getName()].getG()) {
                reached[s.getName()] = child;
                frontier.push(child);
            }
        }
    }*/
    return {};
}

bool AstarSearch::isGoal(Node node)
{
    return node.getState() == goal;
}

std::vector<Node> AstarSearch::expandNode(Node node)
{
    std::vector<Node> childs{};
    
    Cell parent_s = node.getState();
    for (auto action : actions) {
        auto child_s = applyAction(parent_s, action);
        if (child_s.has_value()) {
            int g = node.getG() + actionCost(child_s.value());
            childs.emplace_back(Node{child_s.value(), parent_s, g, computeH(child_s.value())});
        }
    }

    return childs;
}

std::optional<Cell> AstarSearch::applyAction(Cell s, Cell action)
{
    int x = s.getX() + action.getX();
    int y = s.getY() + action.getY();

    bool is_valid_cell = (x >= 0 && x < map.getWidth() && y >= 0 && y < map.getHeight());
    return is_valid_cell ? std::optional<Cell>{Cell{x, y}} : std::nullopt;
}

int AstarSearch::actionCost(Cell child_s)
{
    return map.getValueAt(child_s.getX(), child_s.getY());
}

/*
 * Compute the manhattan distance
 */
int AstarSearch::computeH(Cell state)
{
    return abs(goal.getX() - state.getX()) + abs(goal.getY() - state.getY());
}

}