#include "node.hpp"

namespace {
    // private functions
}

namespace astar {

Node::Node(int state[2], int parent[2], int g, int h) : state{state}, parent{parent}, g{g}, h{h}, f{g+h} {}

Cell Node::getState() const
{
    return state;
}

Cell Node::getParent() const
{
    return parent;
}

int Node::getF() const
{
    return f;
}

int Node::getG() const
{
    return g;
}

int Node::getH() const
{
    return h;
}

}
