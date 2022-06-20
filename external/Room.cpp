#include "Room.hpp"

Room::Room(std::vector<std::array<vecType, 2>> pWalls) : walls(pWalls) {}

std::vector<std::array<vecType, 2>> Room::getWalls() const {
    return walls;
}

void Room::setWalls(std::vector<std::array<vecType, 2>> newWalls) {
    walls = newWalls;
}
