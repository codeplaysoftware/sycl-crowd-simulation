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
 *  Stats.hpp
 *
 *  Description:
 *    Process simulation statistics
 * 
 **************************************************************************/

#ifdef STATS
#include "Actor.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sycl/sycl.hpp>

void updateStats(sycl::queue myQueue, sycl::buffer<Actor> actorBuf,
                 std::vector<float> &averageForces,
                 std::vector<std::array<int, 2>> &destinationTimes,
                 std::chrono::high_resolution_clock::time_point startPoint,
                 int timestep);

void finalizeStats(sycl::queue myQueue, std::vector<float> averageForces,
                   std::vector<std::array<int, 2>> destinationTimes,
                   std::vector<int> kernelDurations, int numActors,
                   int totalExecutionTime);
#endif
