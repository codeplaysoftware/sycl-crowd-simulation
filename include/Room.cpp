#include "Room.hpp"
#include <iostream>
#include <vector>
#include <array>

Room::Room(std::vector<std::array<GeometricVector, 2>> pWalls) {
    walls = pWalls;
}

std::vector<std::array<GeometricVector, 2>> Room::getWalls() {
    return walls;
}
