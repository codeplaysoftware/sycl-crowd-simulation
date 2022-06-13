#ifndef MathHelper_hpp
#define MathHelper_hpp

#include <iostream>
#include <vector>
#include <array>
#include <sycl/sycl.hpp>
#include "GeometricVector.hpp"

SYCL_EXTERNAL GeometricVector getDirectionVector(GeometricVector a, GeometricVector b);

SYCL_EXTERNAL GeometricVector velFromSpeedAndDir(float s, GeometricVector d);

SYCL_EXTERNAL GeometricVector velToPoint(float s, GeometricVector pos, GeometricVector destination);

SYCL_EXTERNAL float magnitude(GeometricVector inp);

SYCL_EXTERNAL float dotProduct(GeometricVector a, GeometricVector b);

SYCL_EXTERNAL float distanceToWall(GeometricVector a, std::array<float, 4> w);

#endif
