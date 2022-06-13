#include "MathHelper.hpp"
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <sycl/sycl.hpp>

SYCL_EXTERNAL GeometricVector getDirectionVector(GeometricVector a, GeometricVector b) {
    return b - a;
}

GeometricVector velFromSpeedAndDir(float s, GeometricVector d) {
    return d * (s / magnitude(d));
}

GeometricVector velToPoint(float s, GeometricVector pos, GeometricVector destination) {
    return velFromSpeedAndDir(s, getDirectionVector(pos, destination));
}

float magnitude(GeometricVector inp) {
    return std::sqrt((inp[0] * inp[0]) + (inp[1] * inp[1]));
}
