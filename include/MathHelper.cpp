#include "MathHelper.hpp"
#include "GeometricVector.hpp"
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <algorithm>
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

SYCL_EXTERNAL float distance(GeometricVector a, GeometricVector b) {
    return magnitude(a - b);
}

SYCL_EXTERNAL float distanceToWall(GeometricVector a, std::array<GeometricVector, 2> w) {
    float lSquared = pow(magnitude(w[1] - w[0]), 2);
    if (lSquared == 0.0) {
        return distance(a, w[0]);
    }
    float t = std::max(float(0.0), std::min(float(1.0), dotProduct(a - w[0], w[1] - w[0]) / lSquared));
    auto projection = w[0] + t * (w[1] - w[0]);
    return distance(a, projection);
}

