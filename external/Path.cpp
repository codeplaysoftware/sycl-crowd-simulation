#include "Path.hpp"

Path::Path(int pId,
           std::array<std::array<vecType, 2>, PATHALLOCATIONSIZE> pCheckpoints,
           int pPathSize)
    : id(pId), checkpoints(pCheckpoints), pathSize(pPathSize) {}

SYCL_EXTERNAL int Path::getId() const { return id; }

SYCL_EXTERNAL std::array<std::array<vecType, 2>, PATHALLOCATIONSIZE>
Path::getCheckpoints() const {
    return checkpoints;
}

SYCL_EXTERNAL int Path::getPathSize() const { return pathSize; }

void Path::setId(int newId) { id = newId; }

void Path::setCheckpoints(
    std::array<std::array<vecType, 2>, PATHALLOCATIONSIZE> newCheckpoints) {
    checkpoints = newCheckpoints;
}
