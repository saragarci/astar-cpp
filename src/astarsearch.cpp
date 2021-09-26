#include "astarsearch.hpp"

namespace {
    // private functions
}

namespace astar {

AstarSearch::AstarSearch(Map map, int start[2], int goal[2]) : map{map}, start{start}, goal{goal}
{
    int move_up[2] = {0,1};
    int move_down[2] = {0,-1};
    int move_left[2] = {-1,0};
    int move_right[2] = {1,0};

    actions.emplace_back(move_up);
    actions.emplace_back(move_down);
    actions.emplace_back(move_left);
    actions.emplace_back(move_right);
}

void AstarSearch::showShortestPath()
{
    Node * result = BestFirstSearch();
    if (result == nullptr) std::cerr << "Failure\n";

    std::vector<Cell> solution{};
    solution.emplace_back(node->getState());

    Node n = node->getParent();
    while (n) {
        auto state = n.getState();
        solution.emplace_back(state);
        n = n.getParent();
    }
    solution.emplace_back(n.getState());

    //map.printSolution(solution);
}

Node * AstarSearch::BestFirstSearch()
{
    while (!frontier.empty()) {
        Node node = frontier.pop();
        if (isGoal(node))
            return &node;

        for (Node child : expandNode(node)) {
            Cell s = child.getState();
            auto search = reached.find(s);
            if (search != reached.end() || child.getG() < reached[s].getG()) {
                reached[s] = child;
                frontier.push(child);
            }
        }
    }
    return nullptr;
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
        Cell * child_s = applyAction(parent_s, action);
        if (child_s != nullptr) {
            int g = node.getG() + actionCost(child_s);
            childs.emplace_back(Node{child_s, parent_s, g, computeH(child_s)});
        }
    }

    return childs;
}

Cell * AstarSearch::applyAction(Cell s, int action[2])
{
    int x = s.getX() + action[0];
    int y = s.getY() + action[1];

    if (x >= 0 && x < map.size() && y >= 0 && y < map[x].size())
        return map[x][y] != -1;
}

int AstarSearch::actionCost(Cell child_s)
{
    return map[child_s.getX()][child_s.getY()];
}

/*
 * Compute the manhattan distance
 */
int AstarSearch::computeH(Cell state)
{
    return abs(goal.getX() - state.getX()) + abs(goal.getY() - state.getY());
}

}