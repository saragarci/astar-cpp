#ifndef CELL_HPP_INCLUDED
#define CELL_HPP_INCLUDED

namespace astar {

class Cell {
public:
    explicit Cell(int cell[2]);
    int getX();
    int getY();

private:
    int x;
    int y;
};

}

#endif
