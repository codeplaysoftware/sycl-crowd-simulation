#ifndef Path_hpp
#define Path_hpp

#include <iostream>
#include <array>
#include <sycl/sycl.hpp>
#include "VectorMaths.hpp"

const int PATHALLOCATIONSIZE = 10;

class Path {
private:
    int id;
    std::array<vecType, PATHALLOCATIONSIZE> checkpoints;
    int pathSize;
public:
    Path(int pId, std::array<vecType, PATHALLOCATIONSIZE> pCheckpoints, int pPathSize);

    SYCL_EXTERNAL int getId() const;
    SYCL_EXTERNAL std::array<vecType, PATHALLOCATIONSIZE> getCheckpoints() const;
    SYCL_EXTERNAL int getPathSize() const;

    void setId(int newId);
    void setCheckpoints(std::array<vecType, PATHALLOCATIONSIZE> newCheckpoints);
};

#endif
