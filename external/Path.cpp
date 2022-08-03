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
 *  Path.cpp
 *
 *  Description:
 *    Class denoting path an actor follows
 * 
 **************************************************************************/

#include "Path.hpp"

Path::Path(int pId,
           std::array<std::array<sycl::float2, 2>, PATHALLOCATIONSIZE> pCheckpoints,
           int pPathSize)
    : id(pId), checkpoints(pCheckpoints), pathSize(pPathSize) {}

SYCL_EXTERNAL int Path::getId() const { return id; }

SYCL_EXTERNAL std::array<std::array<sycl::float2, 2>, PATHALLOCATIONSIZE>
Path::getCheckpoints() const {
    return checkpoints;
}

SYCL_EXTERNAL int Path::getPathSize() const { return pathSize; }

void Path::setId(int newId) { id = newId; }

void Path::setCheckpoints(
    std::array<std::array<sycl::float2, 2>, PATHALLOCATIONSIZE> newCheckpoints) {
    checkpoints = newCheckpoints;
}
