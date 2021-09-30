#include "map.hpp"
#include "astarsearch.hpp"
#include "cell.hpp"

#include <iostream>
#include <array>

using astar::Map;
using astar::AstarSearch;
using astar::Cell;

int main() {
    constexpr std::size_t kCellSize{20};

    std::array<int, 2> north{0,1};
    std::array<int, 2> south{0,-1};
    std::array<int, 2> west{-1,0};
    std::array<int, 2> est{1,0};
    std::array<std::array<int, 2>, 4> actions{north, south, west, est};

    /* Task 0 */
    //Map map_task0{"../src/maps/map_1.csv", kCellSize};
    //std::array<int, 2> start_task0{0,0};
    //std::array<int, 2> goal_task0{9,4};
    //AstarSearch astar_task0(map_task0, start_task0, goal_task0, actions);
    //astar_task0.showShortestPath();

    /* Task 1 */
    //Map map_task1{"../src/maps/Samfundet_map_1.csv", kCellSize};
    //std::array<int, 2> start_task1{18,27};
    //std::array<int, 2> goal_task1{32,40};   
    //AstarSearch astar_task1(map_task1, start_task1, goal_task1, actions);
    //astar_task1.showShortestPath();

    // Task 2
    //Map map_task2{"../src/maps/Samfundet_map_1.csv", kCellSize};
    //std::array<int, 2> start_task2{32,40};
    //std::array<int, 2> goal_task2{5,8};     
    //AstarSearch astar_task2(map_task2, start_task2, goal_task2, actions);
    //astar_task2.showShortestPath();

    // Task 3
    Map map_task3{"../src/maps/Samfundet_map_2.csv", kCellSize};
    std::array<int, 2> start_task3{32,28};
    std::array<int, 2> goal_task3{32,6}; 
    AstarSearch astar_task3(map_task3, start_task3, goal_task3, actions);

    // Task 4
    //Map map_task4{"../src/maps/Samfundet_map_Edgar_full.csv", kCellSize};
    //std::array<int, 2> start_task4{32,28};
    //std::array<int, 2> goal_task4{32,6}; 
    //AstarSearch astar_task4(map_task4, start_task4, goal_task4, actions);
    
    SDL_Event e;
    // Get user input to terminate the program
    while (!(e.type == SDL_QUIT)) {
        SDL_PollEvent(&e);
        if (!astar_task3.getSolutionFound())
            astar_task3.showShortestPath();
        else
            map_task3.print();
    }

    /*
    elif task == 5:
        start_pos = [14, 18]
        goal_pos = [6, 36]
        end_goal_pos = [6, 7]
        path_to_map = 'Samfundet_map_2.csv'
    */
}
