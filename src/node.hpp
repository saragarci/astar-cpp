#ifndef NODE_HPP_INCLUDED
#define NODE_HPP_INCLUDED

#include "cell.hpp"

#include <vector>
#include <optional>

namespace astar {

class Node {
public:
    explicit Node(Cell * state, Cell * parent, int g, int h);
    Cell * getState() const;
    Cell * getParent() const;
    int getF() const;
    int getG() const;
    int getH() const;

private:
    Cell * state;
    Cell * parent;
    int g{0};
    int h{0};
    int f{0};
};

}

#endif
