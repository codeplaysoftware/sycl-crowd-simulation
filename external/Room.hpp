#ifndef Room_hpp
#define Room_hpp

#include <iostream>
#include <array>
#include <sycl/sycl.hpp>
#include "VectorMaths.hpp"

using vecType = std::array<float, 2>;

class Room {
private:
    typedef sycl::usm_allocator<std::array<vecType, 2>, sycl::usm::alloc::shared> vectorAlloc;
    std::vector<std::array<vecType, 2>> walls;
public:    
    Room(std::vector<std::array<vecType, 2>> pWalls);

    std::vector<std::array<vecType, 2>> getWalls() const;

    void setWalls(std::vector<std::array<vecType, 2>> newWalls);
};

#endif
