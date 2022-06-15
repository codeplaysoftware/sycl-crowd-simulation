#include "Room.hpp"
#include "VectorMaths.hpp"
#include <iostream>
#include <vector>
#include <array>
#include <sycl/sycl.hpp>

Room::Room(std::vector<std::array<vecType, 2>> pWalls) {
    walls = pWalls;
}

std::vector<std::array<vecType, 2>> Room::getWalls() {
    return walls;
}
