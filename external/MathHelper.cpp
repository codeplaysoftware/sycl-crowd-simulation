#include "MathHelper.hpp"
#include "VectorMaths.hpp"
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <algorithm>
#include <sycl/sycl.hpp>

SYCL_EXTERNAL vecType getDirectionVector(vecType from, vecType to) {
    return to - from;
}

SYCL_EXTERNAL vecType velFromSpeedAndDir(float s, vecType d) {
    return d * (s / magnitude(d));
}

SYCL_EXTERNAL vecType velToPoint(float s, vecType pos, vecType destination) {
    return velFromSpeedAndDir(s, getDirectionVector(pos, destination));
}

SYCL_EXTERNAL float magnitude(vecType inp) {
    return std::sqrt((inp[0] * inp[0]) + (inp[1] * inp[1]));
}

SYCL_EXTERNAL float dotProduct(vecType a, vecType b) {
    return (a[0] * b[0]) + (a[1] * b[1]);
}

SYCL_EXTERNAL float distance(vecType from, vecType to) {
    return magnitude(from - to);
}

SYCL_EXTERNAL float distanceToWall(vecType point, std::array<vecType, 2> wall) {
    float lSquared = pow(magnitude(wall[1] - wall[0]), 2) +0.01f;
    if (lSquared == 0.0) {
        return distance(point, wall[0]);
    }
    float t = std::max(float(0.0), std::min(float(1.0), dotProduct(point - wall[0], wall[1] - wall[0]) / lSquared));
    auto projection = wall[0] + t * (wall[1] - wall[0]);
    return distance(point, projection); 
}

SYCL_EXTERNAL vecType normalize(vecType inp) {
    return inp / magnitude(inp);
}

SYCL_EXTERNAL vecType getniw(vecType point, std::array<vecType, 2> wall) {
    vecType AB = wall[1] - wall[0];
    vecType BP = point - wall[1];
    vecType AP = point - wall[0];

    float ABdotBP = dotProduct(AB, BP);
    float ABdotAP = dotProduct(AB, AP);

    if (ABdotBP >= 0) {
        return normalize(point - wall[1]);
    }
    else if (ABdotAP < 0) {
        return normalize(point - wall[0]);
    }
    else {
        float lSquared = pow(magnitude(wall[1] - wall[0]), 2);
        if (lSquared == 0.0) {
            return {0, 0};
        }
        float t = std::max(float(0.0), std::min(float(1.0), dotProduct(point - wall[0], wall[1] - wall[0]) / lSquared));
        auto projection = t * AB;
        
        return normalize(AP - projection);
    }
}
