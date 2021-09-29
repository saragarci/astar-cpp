#ifndef CELL_HPP_INCLUDED
#define CELL_HPP_INCLUDED

#include <SDL.h>
#include <string>

namespace astar {

class Cell {
public:
    explicit Cell(int x_coord, int y_coord, int x, int y, int w, int h, int value);
    SDL_Rect *getRect();
    int getXCoord() const;
    int getYCoord() const;
    int getX() const;
    int getY() const;
    std::string getName() const;
    int getValue();
    bool getIsSolution();
    void setIsSolution(bool is_solution);
    bool getIsStart();
    void setIsStart(bool is_start);
    bool getIsGoal();
    void setIsGoal(bool is_goal);

    friend bool operator==(const Cell& lhs, const Cell& rhs) {
        return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY();
    }

private:
    int x;
    int y;
    SDL_Rect rect;
    int value;
    bool isSolution{false};
    bool isStart{false};
    bool isGoal{false};
};

}

#endif
