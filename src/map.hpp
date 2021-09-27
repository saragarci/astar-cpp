#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include <string>
#include <vector>

namespace astar {

class Map {
public:
    explicit Map(std::string path);
    std::vector<std::vector<int>> getMap();
    void print();
    int getWidth() const;
    int getHeight() const;
    int getValueAt(int x, int y) const;

private:
    void createMap();
    std::vector<int> parseLine(std::string line);

    std::string path;
    std::vector<std::vector<int>> map{};
};

}

#endif
