#include "Room.hpp"
#include "GeometricVector.hpp"
#include <iostream>
#include <vector>
#include <array>
#include <sycl/sycl.hpp>

Room::Room(std::vector<std::array<GeometricVector, 2>> pWalls) {
    walls = pWalls;
}

std::vector<std::array<GeometricVector, 2>> Room::getWalls() {
    return walls;
}
