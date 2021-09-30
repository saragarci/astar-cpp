#include "map.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

namespace astar {

/** 
 * Constructor for the Map class
 */
Map::Map(std::string path, const std::size_t kcell_size)
     : path{path}, kcell_size{kcell_size}
{
    // Initialize the video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;

    // Create the map according to the csv provided
    createMap();

    // Compute the screen size based on the number of cells our map has
    const std::size_t screen_width = getWidth()*getCellSize();
    const std::size_t screen_height = getHeight()*getCellSize();
    
    // Create a window
    sdl_window = SDL_CreateWindow("A* Search", SDL_WINDOWPOS_CENTERED, 
                                  SDL_WINDOWPOS_CENTERED, screen_width, 
                                  screen_height, SDL_WINDOW_SHOWN);
    if (sdl_window == nullptr)
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;

    // Create render to draw to the window
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (sdl_renderer == nullptr)
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
}

/** 
 * Destructor for the Map class
 */
Map::~Map()
{
    // Release SDL resources
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

/** 
 * Creates the map by reading the csv file
 */
void Map::createMap()
{
    std::ifstream map_file(path);
    if (!map_file) std::cerr << "no file\n";

    int y{0};
    for (std::string line; std::getline(map_file,line);) {
        parseLine(line, y);
        ++y;
    }     
}

/*
 * Gets a line of the csv file and creates and stores
 * a vector of cells into the map container member.
 * Each integer of the line is used to create a cell.
 */
void Map::parseLine(std::string line, int y)
{
    // Make each line end with a comma
    line += ",";

    int cellSize = static_cast<int>(getCellSize());

    // Read each csv line
    std::istringstream sline(line);
    int n;
    char ch;
    int x{0};
    std::vector<Cell> v;
    while (sline >> n >> ch && ch == ',') {
        v.emplace_back(Cell{x, y, x*cellSize, y*cellSize, cellSize, cellSize, n});
        ++x;
    }
    map.emplace_back(v);
}

/*
 * Renders the cells using the SDL library with different
 * colors according to their state
 */
void Map::print()
{
    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 1);
    SDL_RenderClear(sdl_renderer);

    for (auto row : map) {
        for (auto cell : row) {
            if (cell.getIsStart())
                SDLfillRect(cell, 255, 51, 255);
            else if (cell.getIsGoal())
                SDLfillRect(cell, 0, 128, 255);
            else if (cell.getIsSolution())
                SDLfillRect(cell, 0, 255, 0);
            else if (cell.getIsReached())
                SDLfillRect(cell, 0, 0, 255);
            else if (cell.getValue() == -1)
                SDLfillRect(cell, 35, 160, 225);
            else if (cell.getValue() == 1)
                SDLdrawRect(cell, 224, 224, 224);
            else if (cell.getValue() == 2)
                SDLfillRect(cell, 160, 160, 160);
            else if (cell.getValue() == 3)
                SDLfillRect(cell, 96, 96, 96);
            else if (cell.getValue() == 4)
                SDLfillRect(cell, 32, 32, 32);
        }
    }
    
    // Update Screen
    SDL_RenderPresent(sdl_renderer);
}

/*
 * Helper method to paint a rectangle given a cell and
 * and a specific RGB color specified
 */
void Map::SDLfillRect(Cell cell, int r, int g, int b)
{
    SDL_SetRenderDrawColor(sdl_renderer, r, g, b, 1);
    SDL_RenderFillRect(sdl_renderer, cell.getRect());
}

/*
 * Helper method to draw a rectangle given a cell and
 * and a specific RGB color
 */
void Map::SDLdrawRect(Cell cell, int r, int g, int b)
{
    SDL_SetRenderDrawColor(sdl_renderer, r, g, b, 1);
    SDL_RenderDrawRect(sdl_renderer, cell.getRect());
}

/*
 * Return the width of the map containers
 */
int Map::getWidth() const
{
    return map[0].size();
}

/*
 * Return the height of the map container
 */
int Map::getHeight() const
{
    return map.size();
}

/*
 * Returns the size of the cell (both width and
 * height since they are a square)
 */
std::size_t Map::getCellSize() const
{
    return kcell_size;
}

/*
 * Returns a pointer to the start cell
 */
Cell * Map::getStart() const
{
    return start;
}

/*
 * Returns a pointer to the goal cell
 */
Cell * Map::getGoal() const
{
    return goal;
}

/*
 * Given a position in the map (x, y) sets the
 * start cell
 */
void Map::setStart(std::array<int, 2> new_start)
{
    Cell * start_p = getCellAtCoordinates(new_start[0], new_start[1]);
    if (start_p == nullptr) {
        std::cerr << "start cell doesn't exist\n";
        return;
    }
    start = start_p;
    start->setIsStart(true);
}

/*
 * Given a position in the map (x, y) sets the
 * goal cell
 */
void Map::setGoal(std::array<int, 2> new_goal)
{
    Cell * goal_p = getCellAtCoordinates(new_goal[0], new_goal[1]);
    if (goal_p == nullptr) {
        std::cerr << "goal cell doesn't exist\n";
        return;
    }
    goal = goal_p;
    goal->setIsGoal(true);
}

/*
 * Given a position in the map (x, y) returns a
 * pointer to the cell in that position or nullptr
 * if that position does not exist in the map
 */
Cell * Map::getCellAtCoordinates(int x, int y)
{
    bool valid_cell = x >= 0 && x < getWidth() && y >= 0 && y < getHeight();
    if (!valid_cell)
        return nullptr;
    
    auto * cell = &map[y][x];
    assert(cell);
    return cell;
}

}
