#ifndef DifferentialEqu_hpp
#define DifferentialEqu_hpp

#include "Actor.hpp"
#include "Heatmap.hpp"
#include "MathHelper.hpp"
#include "Path.hpp"
#include "VectorMaths.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <sycl/sycl.hpp>

// Constant for scaling inter-actor repulsive force
constexpr float PEOPLEAi = 500;
// Constant for scaling actor-wall repulsive force
constexpr float WALLAi = 1300;
// Reproduces distance kept at normal desired velocities
constexpr float Bi = 0.08;
// Obstruction effect
constexpr float K1 = 125000;
// Obstruction effect
constexpr float K2 = 240000;
// Characteristic time
constexpr float Ti = 0.5;

// Integration timestep
constexpr float TIMESTEP = 0.001;

SYCL_EXTERNAL void differentialEq(
    int currentIndex,
    sycl::accessor<Actor, 1, sycl::access::mode::read_write> actors,
    sycl::accessor<std::array<vecType, 2>, 1, sycl::access::mode::read> walls,
    sycl::accessor<Path, 1, sycl::access::mode::read> paths, sycl::stream out);

#endif
