#ifndef ASTARSEARCH_HPP_INCLUDED
#define ASTARSEARCH_HPP_INCLUDED

#include "map.hpp"
#include "node.hpp"
#include "cell.hpp"

#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <optional>
#include <array>

namespace astar {

class AstarSearch {
public:
    explicit AstarSearch(Map & map, std::array<int, 2> start, std::array<int, 2> goal, std::array<std::array<int, 2>, 4> actions);
    void showShortestPath();
    void setSolutionFound(bool isSolved);
    bool getSolutionFound();

private:
    std::optional<Node> BestFirstSearch();
    bool isGoal(Node node);
    std::vector<Node> expandNode(Node node);
    Cell * applyAction(Cell * s, std::array<int, 2> action);
    int actionCost(Cell * child_s);
    int computeH(Cell * state);

    Map & map;

    struct cmp {
        auto operator()( Node const lhs, Node const rhs ) const
            -> bool
        { return lhs.getF() > rhs.getF(); }
    };

    std::priority_queue<Node, std::vector<Node>, cmp> frontier;
    std::unordered_map<std::string, Node> reached;

    std::array<std::array<int, 2>, 4> actions;
    bool solutionFound{false};
};

}

#endif
