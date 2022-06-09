#include "Room.hpp"
#include <iostream>
#include <vector>
#include <array>

Room::Room(std::vector<std::array<float, 4>> pWalls, std::vector<std::array<float, 2>> pDestinations) {
    walls = pWalls;
    destinations = pDestinations;
}

std::vector<std::array<float, 4>> Room::getWalls() {
    return walls;
}

std::vector<std::array<float, 2>> Room::getDestinations() {
    return destinations;
}