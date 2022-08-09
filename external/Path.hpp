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
 *  Path.hpp
 *
 *  Description:
 *    Class denoting path an actor follows
 *
 **************************************************************************/

#ifndef Path_hpp
#define Path_hpp

#include <array>
#include <iostream>
#include <sycl/sycl.hpp>

// Constant denoting the size of the array used to store paths
// SYCL kernels can't use dynamic vectors, so paths are stored in
// a fixed-size array, so the path size can't exceed this constant
const int PATH_ALLOCATION_SIZE = 10;

class Path {
  private:
    std::array<sycl::float4, PATH_ALLOCATION_SIZE> checkpoints;
    int id;
    int pathSize;

  public:
    Path(int pId, std::array<sycl::float4, PATH_ALLOCATION_SIZE> pCheckpoints,
         int pPathSize);

    SYCL_EXTERNAL int getId() const;
    SYCL_EXTERNAL std::array<sycl::float4, PATH_ALLOCATION_SIZE>
    getCheckpoints() const;
    SYCL_EXTERNAL int getPathSize() const;

    void setId(int newId);
    void setCheckpoints(
        std::array<sycl::float4, PATH_ALLOCATION_SIZE> newCheckpoints);
};

#endif
