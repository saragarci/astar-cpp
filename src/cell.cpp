#include "cell.hpp"

namespace {
    // private functions
}

namespace astar {

Cell::Cell(int x_coord, int y_coord, int x, int y, int w, int h, int value)
     : x{x_coord}, y{y_coord}, rect{x, y, w, h}, value{value} {}

SDL_Rect * Cell::getRect()
{
    return &rect;
}

int Cell::getXCoord() const
{
    return x;
}

int Cell::getYCoord() const
{
    return y;
}

int Cell::getX() const
{
    return rect.x;
}

int Cell::getY() const
{
    return rect.y;
}

std::string Cell::getName() const
{
    return "(" + std::to_string(getXCoord()) + "," + std::to_string(getYCoord()) + ")";
}

int Cell::getValue()
{
    return value;
}

bool Cell::getIsSolution()
{
    return isSolution;
}

void Cell::setIsSolution(bool is_solution)
{
    isSolution = is_solution;
}

bool Cell::getIsStart()
{
    return isStart;
}

void Cell::setIsStart(bool is_start)
{
    isStart = is_start;
}

bool Cell::getIsGoal()
{
    return isGoal;
}

void Cell::setIsGoal(bool is_goal)
{
    isGoal = is_goal;
}

bool Cell::getIsReached()
{
    return isReached;
}

void Cell::setIsReached(bool is_reached)
{
    isReached = is_reached;
}

}
