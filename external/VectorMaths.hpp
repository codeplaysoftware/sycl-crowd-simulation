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
 *  VectorMaths.hpp
 *
 *  Description:
 *    Operator overloading for common operators on vectors
 * 
 **************************************************************************/

#ifndef VectorMaths_hpp
#define VectorMaths_hpp

#include <array>
#include <cmath>
#include <iostream>
#include <sycl/sycl.hpp>

// Any file which includes VectorMaths.hpp will have this alias
using vecType = std::array<float, 2>;

SYCL_EXTERNAL vecType operator*=(vecType &a, vecType b);
SYCL_EXTERNAL vecType operator*(vecType a, vecType b);

SYCL_EXTERNAL vecType operator+=(vecType &a, vecType b);
SYCL_EXTERNAL vecType operator+(vecType a, vecType b);

SYCL_EXTERNAL vecType operator-=(vecType &a, vecType b);
SYCL_EXTERNAL vecType operator-(vecType a, vecType b);

SYCL_EXTERNAL vecType operator*=(vecType &a, float s);
SYCL_EXTERNAL vecType operator*(vecType a, float s);
SYCL_EXTERNAL vecType operator*=(float s, vecType &a);
SYCL_EXTERNAL vecType operator*(float s, vecType a);

SYCL_EXTERNAL vecType operator/=(vecType &a, float s);
SYCL_EXTERNAL vecType operator/(vecType a, float s);

#endif
