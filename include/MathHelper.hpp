#ifndef MathHelper_hpp
#define MathHelper_hpp

#include <iostream>
#include <vector>
#include <array>

std::array<float, 2> getDirectionVector(std::array<float, 2> a, std::array<float, 2> b);

std::array<float, 2> velFromSpeedAndDir(float s, std::array<float, 2> d);

std::array<float, 2> velToPoint(float s, std::array<float, 2> pos, std::array<float, 2> destination);

float magnitude(std::array<float, 2> inp);

#endif