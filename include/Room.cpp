#include "Room.hpp"
#include <iostream>
#include <vector>
#include <array>

Room::Room(std::vector<std::array<float, 4>> pWalls) {
    walls = pWalls;
}

std::vector<std::array<float, 4>> Room::getWalls() {
    return walls;
}