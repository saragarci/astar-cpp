#ifndef ASTARSEARCH_HPP_INCLUDED
#define ASTARSEARCH_HPP_INCLUDED

#include "map.hpp"
#include "node.hpp"
#include "cell.hpp"

#include <vector>
#include <queue>
#include <unordered_map>

namespace astar {

class AstarSearch {
public:
    explicit AstarSearch(Map map, int start[2], int goal[2]);
    void showShortestPath();

private:
    Node BestFirstSearch();
    bool isGoal(Node node);
    std::vector<Node> expandNode(Node node);
    Cell * applyAction(Cell s, int action[2]);
    int actionCost(Cell child_s);
    int computeH(Cell state);

    Map map;
    Cell start;
    Cell goal;
    std::priority_queue<Node> frontier;
    std::unordered_map<Cell, Node> reached;
    std::vector<std::array<int,2>> actions;
};

}

#endif
