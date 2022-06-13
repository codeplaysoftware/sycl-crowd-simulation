#ifndef Room_hpp
#define Room_hpp

#include <iostream>
#include <vector>
#include <array>
#include "GeometricVector.hpp"

class Room {
private:
    std::vector<std::array<GeometricVector, 2>> walls;
public:    
    Room(std::vector<std::array<GeometricVector, 2>> pWalls);

    std::vector<std::array<GeometricVector, 2>> getWalls();
};

#endif
