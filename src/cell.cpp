#include "cell.hpp"

namespace {
    // private functions
}

namespace astar {

Cell::Cell(int cell[2]) : x{cell[0]}, y{cell[1]} {}

int Cell::getX()
{
    return x;
}

int Cell::getY()
{
    return y;
}

}
