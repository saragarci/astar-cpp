#include "map.hpp"
#include "astarsearch.hpp"
#include "cell.hpp"

#include <iostream>
#include <array>

using astar::Map;
using astar::AstarSearch;
using astar::Cell;

struct Task {
    Task(std::string map_path, std::array<int, 2> start, std::array<int, 2> goal)
         : map_path{map_path}, start{start}, goal{goal} {}

    std::size_t kCellSize{10};

    std::array<int, 2> north{0,1};
    std::array<int, 2> south{0,-1};
    std::array<int, 2> west{-1,0};
    std::array<int, 2> est{1,0};
    std::array<std::array<int, 2>, 4> actions{north, south, west, est};

    std::string map_path;
    std::array<int, 2> start;
    std::array<int, 2> goal;
};

/** 
 * Main method to run each task.
 * Task needs to be specified as a command argument
 * For example to run task 1:
 * ./Astarsearch 1
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Task number missing!\n";
        return 0;
    }

    Task * task = nullptr;

    // Task 0
    if (strcmp(argv[1], "0") == 0) {
        Task task0{"../src/maps/map_1.csv", std::array<int, 2>{0,0}, std::array<int, 2>{9,4}};
        task = &task0;
    }

    // Task 1
    else if (strcmp(argv[1], "1") == 0) {
        Task task1{"../src/maps/Samfundet_map_1.csv", std::array<int, 2>{18,27}, std::array<int, 2>{32,40}};
        task = &task1;
    }

    // Task 2
    else if (strcmp(argv[1], "2") == 0) {
        Task task2{"../src/maps/Samfundet_map_1.csv", std::array<int, 2>{32,40}, std::array<int, 2>{5,8}};
        task = &task2;
    }

    // Task 3
    else if (strcmp(argv[1], "3") == 0) {
        Task task3{"../src/maps/Samfundet_map_2.csv", std::array<int, 2>{32,28}, std::array<int, 2>{32,6}};
        task = &task3;
    }

    // Task 4
    else if (strcmp(argv[1], "4") == 0) {
        Task task4{"../src/maps/Samfundet_map_Edgar_full.csv", std::array<int, 2>{32,28}, std::array<int, 2>{32,6}};
        task = &task4;
    }

    assert(task);

    // Instantiate a map and the astar search
    Map map{task->map_path, task->kCellSize};
    AstarSearch astar(map, task->start, task->goal, task->actions);

    SDL_Event e;
    // Get user input to terminate the program
    while (!(e.type == SDL_QUIT)) {
        SDL_PollEvent(&e);
        if (!astar.getSolutionFound())
            astar.showShortestPath();
        else
            map.print();
    }
}
