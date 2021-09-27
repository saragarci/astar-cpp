#include "map.hpp"
#include "astarsearch.hpp"
#include "cell.hpp"

#include <iostream>

using astar::Map;
using astar::AstarSearch;
using astar::Cell;

int main() {
    // Task 0
    Map map{"../src/maps/map_1.csv"};
    map.print();
    
    Cell start{0,0};
    Cell goal{4,9};    
    
    AstarSearch astar(map, start, goal);
    //astar.showShortestPath();

    std::cout << std::endl;

    // Task 1
    Map map1{"../src/maps/Samfundet_map_1.csv"};
    map1.print();
    
    Cell start1{27,18};
    Cell goal1{40,32};    
    
    AstarSearch astar1(map1, start1, goal1);
    astar1.showShortestPath();
}
