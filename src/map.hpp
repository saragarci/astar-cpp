#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include "cell.hpp"

#include <SDL.h>
#include <string>
#include <vector>
#include <array>

namespace astar {

class Map {
public:
    explicit Map(std::string path, const std::size_t kcell_size);
    ~Map();

    void print();
    int getWidth() const;
    int getHeight() const;
    Cell * getCellAtCoordinates(int x, int y);
    std::size_t getCellSize() const;
    Cell * getStart() const;
    Cell * getGoal() const;
    void setStart(std::array<int, 2> new_start);
    void setGoal(std::array<int, 2> new_goal);

private:
    void createMap();
    void parseLine(std::string line, int y);
    void SDLfillRect(Cell cell, int r, int g, int b);
    void SDLdrawRect(Cell cell, int r, int g, int b);

    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
    const std::size_t kcell_size;
    std::string path;
    std::vector<std::vector<Cell>> map{};
    Cell * start{nullptr};
    Cell * goal{nullptr};
};

}

#endif
