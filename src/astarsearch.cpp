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
    if (!result.has_value()){
        std::cerr << "Failure\n";
        return;
    }

    std::vector<Cell> solution{};
    solution.emplace_back(result->getState());

    auto c_parent = result->getParent();
    while (c_parent.has_value()) {
        const Node n_parent = reached.at(c_parent->getName());
        solution.emplace_back(n_parent.getState());
        c_parent = n_parent.getParent();
    }

    for (auto s : solution)
        std::cout << s.getName() << ", ";
    std::cout << std::endl;

    map.printSolution(solution);
}

std::optional<Node> AstarSearch::BestFirstSearch()
{
    Node n = Node{start, {}, actionCost(start), computeH(start)};
    frontier.push(n);
    reached.insert({start.getName(), n});
    while (!frontier.empty()) {
        const Node node = frontier.top();
        frontier.pop();
        if (isGoal(node))
            return node;

        //std::cout << "Expanding node: " << node.getState().getName() << std::endl;
        for (Node child : expandNode(node)) {
            Cell s = child.getState();
            auto search = reached.find(s.getName());
            if (search == reached.end()) {
                reached.insert({s.getName(), child});
                frontier.push(child);
            } else if (child.getG() < reached.at(s.getName()).getG()) {
                reached.at(s.getName()) = child;
                frontier.push(child);
            }
        }
    }
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

    bool is_cell_in_grid = x >= 0 && x < map.getWidth() && y >= 0 && y < map.getHeight();
    if (!is_cell_in_grid)
        return {};

    bool is_cell_a_valid_path = map.getValueAt(x, y) != 0;
    if (!is_cell_a_valid_path)
        return {};
    
    return std::optional<Cell>{Cell{x, y}};
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
