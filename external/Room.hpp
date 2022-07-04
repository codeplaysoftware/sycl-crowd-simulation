#ifndef Room_hpp
#define Room_hpp

#include "VectorMaths.hpp"
#include <array>
#include <iostream>
#include <sycl/sycl.hpp>

class Room {
  private:
    std::vector<std::array<vecType, 2>> walls;

  public:
    Room(std::vector<std::array<vecType, 2>> pWalls);

    std::vector<std::array<vecType, 2>> getWalls() const;

    void setWalls(std::vector<std::array<vecType, 2>> newWalls);
};

#endif
