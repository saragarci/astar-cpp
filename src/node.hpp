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

    /*friend bool operator<(Node const& lhs, Node const& rhs) {
        return lhs.getF() < rhs.getF();
    }

    friend bool operator<(const Node& n) const { return getF() < n.getF(); }
    friend bool operator>(const Node& n) const { return getF() > n.getF(); }
    friend bool operator==(const Node& lhs, const Node& rhs) {
        return lhs.getF() == rhs.getF();
    }*/

    /*constexpr bool operator()(const Node &lhs, const Node &rhs) const 
    {
        return lhs.getF() > rhs.getF(); // assumes that the implementation uses a flat address space
    }*/


private:
    Cell state;
    std::optional<Cell> parent;
    int g{0};
    int h{0};
    int f{0};
};

}

#endif
