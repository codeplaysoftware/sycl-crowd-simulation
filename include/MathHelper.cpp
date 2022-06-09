#include "MathHelper.hpp"
#include <iostream>
#include <vector>
#include <array>
#include <cmath>

std::array<float, 2> getDirectionVector(std::array<float, 2> a, std::array<float, 2> b) {
    return {float(b[0] - a[0]), float(b[1] - a[1])};
}

std::array<float, 2> velFromSpeedAndDir(float s, std::array<float, 2> d) {
    return {(s / magnitude(d)) * d[0], (s / magnitude(d)) * d[1]};
}

std::array<float, 2> velToPoint(float s, std::array<float, 2> pos, std::array<float, 2> destination) {
    return velFromSpeedAndDir(s, getDirectionVector(pos, destination));
}

float magnitude(std::array<float, 2> inp) {
    return std::sqrt((inp[0] * inp[0]) + (inp[1] * inp[1]));
}