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
 *  MathHelper.hpp
 *
 *  Description:
 *    Collection of helper functions performing common vector math 
 *    operations
 * 
 **************************************************************************/

#ifndef MathHelper_hpp
#define MathHelper_hpp

#include <array>
#include <iostream>
#include <sycl/sycl.hpp>

SYCL_EXTERNAL sycl::float2 getDirectionVector(sycl::float2 a, sycl::float2 b);

SYCL_EXTERNAL sycl::float2 velFromSpeedAndDir(float speed, sycl::float2 direction);

SYCL_EXTERNAL sycl::float2 velToPoint(float speed, sycl::float2 pos, sycl::float2 destination);

SYCL_EXTERNAL float magnitude(sycl::float2 inp);

SYCL_EXTERNAL float inverseMagnitude(sycl::float2 inp);

SYCL_EXTERNAL float dotProduct(sycl::float2 a, sycl::float2 b);

SYCL_EXTERNAL float distance(sycl::float2 a, sycl::float2 b);

SYCL_EXTERNAL sycl::float2 normalize(sycl::float2 inp);

SYCL_EXTERNAL std::pair<float, sycl::float2>
getDistanceAndNiw(sycl::float2 point, std::array<sycl::float2, 2> wall);

SYCL_EXTERNAL sycl::float2 getTangentialVector(sycl::float2 normal);

#endif
