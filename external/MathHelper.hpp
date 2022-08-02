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

#include "VectorMaths.hpp"
#include <array>
#include <iostream>
#include <sycl/sycl.hpp>

SYCL_EXTERNAL vecType getDirectionVector(vecType a, vecType b);

SYCL_EXTERNAL vecType velFromSpeedAndDir(float speed, vecType direction);

SYCL_EXTERNAL vecType velToPoint(float speed, vecType pos, vecType destination);

SYCL_EXTERNAL float magnitude(vecType inp);

SYCL_EXTERNAL float inverseMagnitude(vecType inp);

SYCL_EXTERNAL float dotProduct(vecType a, vecType b);

SYCL_EXTERNAL float distance(vecType a, vecType b);

SYCL_EXTERNAL vecType normalize(vecType inp);

SYCL_EXTERNAL std::pair<float, vecType>
getDistanceAndNiw(vecType point, std::array<vecType, 2> wall);

SYCL_EXTERNAL vecType getTangentialVector(vecType normal);

#endif
