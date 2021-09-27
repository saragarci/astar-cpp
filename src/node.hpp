#ifndef NODE_HPP_INCLUDED
#define NODE_HPP_INCLUDED

#include "cell.hpp"

#include <vector>
#include <optional>

namespace astar {

class Node {
public:
    explicit Node(Cell state, std::optional<Cell> parent, int g, int h);
    Cell getState() const;
    std::optional<Cell> getParent() const;
    int getF() const;
    int getG() const;
    int getH() const;

    bool operator<(const Node& n) const { return getF() < n.getF(); }

private:
    Cell state;
    std::optional<Cell> parent;
    int g{0};
    int h{0};
    int f{0};
};

}

#endif
