#ifndef NODE_HPP_INCLUDED
#define NODE_HPP_INCLUDED

#include "cell.hpp"

#include <vector>

namespace astar {

class Node {
public:
    explicit Node(int state[2], int parent[2], int g, int h);
    Cell getState() const;
    Cell getParent() const;
    int getF() const;
    int getG() const;
    int getH() const;
    bool operator<(const Node& n) const { return getF() < n.getF(); }

private:
    Cell state;
    Cell parent;
    int g{0};
    int h{0};
    int f{0};
};

}

#endif
