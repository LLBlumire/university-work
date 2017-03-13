#include <iostream>
#include "maze.hpp"

int main(void) {
    maze::RawCell<int> my_cell(4);
    std::cout << my_cell.north << std::endl;
    my_cell.north = true;
    std::cout << my_cell.north << std::endl;
}
