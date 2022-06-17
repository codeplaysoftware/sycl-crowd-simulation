#ifndef DifferentialEqu_hpp
#define DifferentialEqu_hpp

#include <iostream>
#include <array>
#include <sycl/sycl.hpp>
#include "Actor.hpp"
#include "MathHelper.hpp"
#include "VectorMaths.hpp"

constexpr float Ai = 200;
constexpr float Bi = 0.08;
constexpr float K1 = 125000;
constexpr float K2 = 240000;
constexpr float Ti = 0.5;

using vecType = std::array<float, 2>;

SYCL_EXTERNAL void differentialEq(int x, sycl::accessor<Actor, 1, sycl::access::mode::read_write> actors, sycl::accessor<std::array<vecType, 2>, 1, sycl::access::mode::read> walls, sycl::stream out);

#endif
