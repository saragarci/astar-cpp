#include "map.hpp"
#include "astarsearch.hpp"
#include "cell.hpp"

using astar::Map;
using astar::AstarSearch;
using astar::Cell;

int main() {
    // Task 0
    Map map{"../src/maps/map_1.csv"};
    map.print();
    
    Cell start{0,0};
    Cell goal{4,9};    
    
    //AstarSearch astar(map, start, goal);
    //astar.showShortestPath();
}
