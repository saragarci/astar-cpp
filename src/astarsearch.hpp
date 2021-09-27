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

namespace astar {

class AstarSearch {
public:
    explicit AstarSearch(Map & map, Cell & start, Cell & goal);
    void showShortestPath();

private:
    std::optional<Node> BestFirstSearch();
    bool isGoal(Node node);
    std::vector<Node> expandNode(Node node);
    std::optional<Cell> applyAction(Cell s, Cell action);
    int actionCost(Cell child_s);
    int computeH(Cell state);

    Map & map;
    Cell & start;
    Cell & goal;

    struct cmp {
        auto operator()( Node const lhs, Node const rhs ) const
            -> bool
        { return lhs.getF() > rhs.getF(); }
    };

    std::priority_queue<Node, std::vector<Node>, cmp> frontier;
    std::unordered_map<std::string, Node> reached;
    std::vector<Cell> actions;
};

}

#endif
