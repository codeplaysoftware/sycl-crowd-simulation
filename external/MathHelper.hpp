#ifndef MathHelper_hpp
#define MathHelper_hpp

#include <iostream>
#include <array>
#include <sycl/sycl.hpp>
#include "VectorMaths.hpp"


SYCL_EXTERNAL vecType getDirectionVector(vecType a, vecType b);

SYCL_EXTERNAL vecType velFromSpeedAndDir(float speed, vecType direction);

SYCL_EXTERNAL vecType velToPoint(float speed, vecType pos, vecType destination);

SYCL_EXTERNAL float magnitude(vecType inp);

SYCL_EXTERNAL float inverseMagnitude(vecType inp);

SYCL_EXTERNAL float dotProduct(vecType a, vecType b);

SYCL_EXTERNAL float distance(vecType a, vecType b);

SYCL_EXTERNAL vecType normalize(vecType inp);

SYCL_EXTERNAL std::pair<float, vecType> getDistanceAndNiw(vecType point, std::array<vecType, 2> wall);

SYCL_EXTERNAL vecType getTangentialVector(vecType normal);

#endif
