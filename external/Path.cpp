#include "Path.hpp"

Path::Path(int pId, std::array<vecType, PATHALLOCATIONSIZE> pCheckpoints, int pPathSize) : id(pId), checkpoints(pCheckpoints), pathSize(pPathSize) {}

SYCL_EXTERNAL int Path::getId() const {
    return id;
}

SYCL_EXTERNAL std::array<vecType, PATHALLOCATIONSIZE> Path::getCheckpoints() const {
    return checkpoints;
}

SYCL_EXTERNAL int Path::getPathSize() const {
    return pathSize;
}

void Path::setId(int newId) {
    id = newId;
} 

void Path::setCheckpoints(std::array<vecType, PATHALLOCATIONSIZE> newCheckpoints) {
    checkpoints = newCheckpoints;
}
