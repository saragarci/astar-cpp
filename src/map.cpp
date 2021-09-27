#include "map.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

namespace {
    // private functions
}

namespace astar {

Map::Map(std::string path) : path{path}
{
    createMap();
}

void Map::createMap()
{
    std::ifstream map_file(path);
    if (!map_file) std::cerr << "no file\n";

    for (std::string line; std::getline(map_file,line);)
        map.emplace_back(parseLine(line));
}

std::vector<int> Map::parseLine(std::string line)
{
    line += ","; // make all lines end with comma
    std::istringstream sline(line);
    std::vector<int> row;
    int n;
    char ch;
    while (sline >> n >> ch && ch == ',') {
        if (n == 1) row.emplace_back(1);
        if (n == -1) row.emplace_back(0);
    }
    return row;
}

std::vector<std::vector<int>> Map::getMap()
{
    return map;
}

void Map::print()
{
    for (auto row : map) {
        for (auto elem : row) {
            if (elem == 8)
                std::cout << " * ";
            else if (elem == -1)
                std::cout << " S ";
            else if (elem == -2)
                std::cout << " G ";
            else
                std::cout << " " << elem << " ";
        }
    
        std::cout << std::endl;
    }
}

int Map::getWidth() const
{
    return map.size();
}

int Map::getHeight() const
{
    return map[0].size();
}

int Map::getValueAt(int x, int y) const
{
    return map[x][y];
}

void Map::printSolution(std::vector<Cell> solution)
{
    for (auto s : solution)
        map[s.getX()][s.getY()] = 8;
    
    auto start = solution[solution.size()-1];
    map[start.getX()][start.getY()] = -1;

    auto goal = solution[0];
    map[goal.getX()][goal.getY()] = -2;
    
    print();
}

}