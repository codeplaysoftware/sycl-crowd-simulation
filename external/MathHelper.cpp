#include "MathHelper.hpp"
#include "GeometricVector.hpp"
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <algorithm>
#include <sycl/sycl.hpp>

SYCL_EXTERNAL GeometricVector getDirectionVector(GeometricVector from, GeometricVector to) {
    return to - from;
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

SYCL_EXTERNAL float distance(GeometricVector from, GeometricVector to) {
    return magnitude(from - to);
}

SYCL_EXTERNAL float distanceToWall(GeometricVector point, std::array<GeometricVector, 2> wall) {
    float lSquared = pow(magnitude(wall[1] - wall[0]), 2);
    if (lSquared == 0.0) {
        return distance(point, wall[0]);
    }
    float t = std::max(float(0.0), std::min(float(1.0), dotProduct(point - wall[0], wall[1] - wall[0]) / lSquared));
    auto projection = wall[0] + t * (wall[1] - wall[0]);
    return distance(point, projection);
}

SYCL_EXTERNAL GeometricVector normalize(GeometricVector inp) {
    return inp / magnitude(inp);
}

SYCL_EXTERNAL GeometricVector getniw(GeometricVector point, std::array<GeometricVector, 2> wall) {
    float lSquared = pow(magnitude(wall[1] - wall[0]), 2);
    if (lSquared == 0.0) {
        return getZeroFromVector(point);
    }
    float t = std::max(float(0.0), std::min(float(1.0), dotProduct(point - wall[0], wall[1] - wall[0]) / lSquared));
    auto projection = wall[0] + t * (wall[1] - wall[0]);
    return normalize(projection);
}
