#include "map.hpp"
#include "astarsearch.hpp"
#include "cell.hpp"

#include <iostream>

using astar::Map;
using astar::AstarSearch;
using astar::Cell;

int main() {
    /* Task 0 */
    Map map_task0{"../src/maps/map_1.csv"};
    //map_task0.print();
    
    Cell start_task0{0,0};
    Cell goal_task0{4,9};    
    
    //AstarSearch astar_task0(map_task0, start_task0, goal_task0);
    //astar_task0.showShortestPath();
    /* ------ */

    /* Task 1 */
    Map map_task1{"../src/maps/Samfundet_map_1.csv"};
    //map_task1.print();
    
    Cell start_task1{27,18};
    Cell goal_task1{40,32};    
    
    //AstarSearch astar_task1(map_task1, start_task1, goal_task1);
    //astar_task1.showShortestPath();
    /* ------ */

    // Task 2
    Map map_task2{"../src/maps/Samfundet_map_1.csv"};
    map_task2.print();
    
    Cell start_task2{40,32};
    Cell goal_task2{8,5};    
    
    AstarSearch astar_task2(map_task2, start_task2, goal_task2);
    astar_task2.showShortestPath();
    /* ------ */

    // Task 3
    Map map_task3{"../src/maps/Samfundet_map_2.csv"};
    //map_task3.print();
    
    Cell start_task3{28,32};
    Cell goal_task3{6,32};    
    
    //AstarSearch astar_task3(map_task3, start_task3, goal_task3);
    //astar_task3.showShortestPath();
    /* ------ */

    // Task 4
    Map map_task4{"../src/maps/Samfundet_map_Edgar_full.csv"};
    //map_task4.print();
    
    Cell start_task4{28,32};
    Cell goal_task4{6,32};    
    
    //AstarSearch astar_task4(map_task4, start_task4, goal_task4);
    //astar_task4.showShortestPath();
    /* ------ */

    /*
    elif task == 5:
        start_pos = [14, 18]
        goal_pos = [6, 36]
        end_goal_pos = [6, 7]
        path_to_map = 'Samfundet_map_2.csv'
    */
}
