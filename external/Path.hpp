#ifndef Path_hpp
#define Path_hpp

#include "VectorMaths.hpp"
#include <array>
#include <iostream>
#include <sycl/sycl.hpp>

// Constant denoting the size of the array used to store paths
// SYCL kernels can't use dynamic vectors, so paths are stored in
// a fixed-size array, so the path size can't exceed this constant
const int PATHALLOCATIONSIZE = 10;

class Path {
  private:
    int id;
    std::array<std::array<vecType, 2>, PATHALLOCATIONSIZE> checkpoints;
    int pathSize;

  public:
    Path(int pId,
         std::array<std::array<vecType, 2>, PATHALLOCATIONSIZE> pCheckpoints,
         int pPathSize);

    SYCL_EXTERNAL int getId() const;
    SYCL_EXTERNAL std::array<std::array<vecType, 2>, PATHALLOCATIONSIZE>
    getCheckpoints() const;
    SYCL_EXTERNAL int getPathSize() const;

    void setId(int newId);
    void setCheckpoints(
        std::array<std::array<vecType, 2>, PATHALLOCATIONSIZE> newCheckpoints);
};

#endif