#include "map.hpp"
#include "astarsearch.hpp"
#include "cell.hpp"

#include <iostream>

using astar::Map;
using astar::AstarSearch;
using astar::Cell;

int main() {
    // Task 0
    Map map_task0{"../src/maps/map_1.csv"};
    //map_task0.print();
    
    Cell start_task0{0,0};
    Cell goal_task0{4,9};    
    
    //AstarSearch astar_task0(map_task0, start_task0, goal_task0);
    //astar_task0.showShortestPath();

    std::cout << std::endl;

    // Task 1
    Map map_task1{"../src/maps/Samfundet_map_1.csv"};
    map_task1.print();
    
    Cell start_task1{27,18};
    Cell goal_task1{40,32};    
    
    AstarSearch astar_task1(map_task1, start_task1, goal_task1);
    astar_task1.showShortestPath();

    std::cout << std::endl;

    // Task 2
    Map map_task2{"../src/maps/Samfundet_map_2.csv"};
    //map_task2.print();
    
    Cell start_task2{27,18};
    Cell goal_task2{40,32};    
    
    //AstarSearch astar_task2(map_task2, start_task2, goal_task2);
    //astar_task2.showShortestPath();
}
