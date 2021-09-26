#include "map.hpp"

#include <iostream>

int main() {
    map::Map map{"../src/maps/map_1.csv"};
    map.print();
}
