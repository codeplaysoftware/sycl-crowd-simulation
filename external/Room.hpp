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
 *  Room.hpp
 *
 *  Description:
 *    Class denoting the environment actors exist in
 *
 **************************************************************************/

#ifndef Room_hpp
#define Room_hpp

#include <array>
#include <iostream>
#include <sycl/sycl.hpp>

class Room {
  private:
    // Each wall is defined as a line with a start and end point
    std::vector<std::array<sycl::float2, 2>> walls;

  public:
    Room(std::vector<std::array<sycl::float2, 2>> pWalls);

    std::vector<std::array<sycl::float2, 2>> getWalls() const;

    void setWalls(std::vector<std::array<sycl::float2, 2>> newWalls);
};

#endif
