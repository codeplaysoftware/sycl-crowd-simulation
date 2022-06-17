#ifndef Room_hpp
#define Room_hpp

#include <iostream>
#include <array>
#include <sycl/sycl.hpp>
#include "VectorMaths.hpp"

using vecType = std::array<float, 2>;

class Room {
private:
    std::vector<std::array<vecType, 2>> walls;
public:    
    Room(std::vector<std::array<vecType, 2>> pWalls);

    std::vector<std::array<vecType, 2>> getWalls() const;
};

#endif
