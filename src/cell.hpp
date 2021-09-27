#ifndef CELL_HPP_INCLUDED
#define CELL_HPP_INCLUDED

#include <string>

namespace astar {

class Cell {
public:
    explicit Cell(int x, int y);
    int getX() const;
    int getY() const;
    std::string getName() const;

    friend bool operator==(const Cell& lhs, const Cell& rhs) {
        return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY();
    }

private:
    int x;
    int y;
};

}

#endif
