#include "cell.hpp"

namespace {
    // private functions
}

namespace astar {

Cell::Cell(int x, int y) : x{x}, y{y} {}

int Cell::getX() const
{
    return x;
}

int Cell::getY() const
{
    return y;
}

std::string Cell::getName() const
{
    return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
}

}
