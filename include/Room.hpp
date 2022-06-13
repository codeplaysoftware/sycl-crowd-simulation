#ifndef Room_hpp
#define Room_hpp

#include <iostream>
#include <vector>
#include <array>
#include <sycl/sycl.hpp>

class Room {
private:
    std::vector<std::array<float, 4>> walls;
public:    
    Room(std::vector<std::array<float, 4>> pWalls);

    SYCL_EXTERNAL std::vector<std::array<float, 4>> getWalls();
};

#endif
