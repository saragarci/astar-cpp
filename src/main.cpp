#include "map.hpp"
#include "astarsearch.hpp"

using astar::Map;
using astar::AstarSearch;

int main() {
    // Task 0
    Map map{"../src/maps/map_1.csv"};
    map.print();
    
    int start[2] = {0,0};    
    int goal[2] = {4,9};
    
    AstarSearch astar(map, start, goal);
    astar.showShortestPath();
}
