#ifndef MathHelper_hpp
#define MathHelper_hpp

#include <iostream>
#include <vector>
#include <array>
#include <sycl/sycl.hpp>
#include "GeometricVector.hpp"

SYCL_EXTERNAL GeometricVector getDirectionVector(GeometricVector a, GeometricVector b);

GeometricVector velFromSpeedAndDir(float s, GeometricVector d);

GeometricVector velToPoint(float s, GeometricVector pos, GeometricVector destination);

float magnitude(GeometricVector inp);

#endif
