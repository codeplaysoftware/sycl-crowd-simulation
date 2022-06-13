#include "MathHelper.hpp"
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <sycl/sycl.hpp>

SYCL_EXTERNAL GeometricVector getDirectionVector(GeometricVector a, GeometricVector b) {
    return b - a;
}

SYCL_EXTERNAL GeometricVector velFromSpeedAndDir(float s, GeometricVector d) {
    return d * (s / magnitude(d));
}

SYCL_EXTERNAL GeometricVector velToPoint(float s, GeometricVector pos, GeometricVector destination) {
    return velFromSpeedAndDir(s, getDirectionVector(pos, destination));
}

SYCL_EXTERNAL float magnitude(GeometricVector inp) {
    return std::sqrt((inp[0] * inp[0]) + (inp[1] * inp[1]));
}

SYCL_EXTERNAL float dotProduct(GeometricVector a, GeometricVector b) {
    return (a[0] * b[0]) + (a[1] * b[1]);
}

SYCL_EXTERNAL float distanceToWall(GeometricVector a, std::array<GeometricVector, 2> w) {
    float numerator = std::fabs(((w[1][0] - w[0][0]) * (w[0][1] - a[1])) - ((w[0][0] - a[0]) * (w[1][1] - w[0][1])));
    float denominator = sqrt(pow((w[1][0] - w[0][0]), 2) + pow((w[1][1] - w[0][1]), 2));
    return float(numerator / denominator);
}
