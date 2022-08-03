/***************************************************************************
 *
 *  Copyright (C) 2022 Codeplay Software Ltd.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  Codeplay's crowd-simulation
 *
 *  DifferentialEq.hpp
 *
 *  Description:
 *    Kernel for calculating social forces
 * 
 **************************************************************************/

#ifndef DifferentialEqu_hpp
#define DifferentialEqu_hpp

#include "Actor.hpp"
#include "Heatmap.hpp"
#include "MathHelper.hpp"
#include "Path.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <sycl/sycl.hpp>

// Constant for scaling inter-actor repulsive force
constexpr float PEOPLEAi = 800;
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
    int actorIndex,
    sycl::accessor<Actor, 1, sycl::access::mode::read_write> actors,
    sycl::accessor<std::array<sycl::float2, 2>, 1, sycl::access::mode::read> walls,
    sycl::accessor<Path, 1, sycl::access::mode::read> paths,
    sycl::accessor<bool, 1, sycl::access::mode::read> heatmapEnabled);

#endif
