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
 *  VectorMaths.cpp
 *
 *  Description:
 *    Operator overloading for common operators on vectors
 * 
 **************************************************************************/

#include "VectorMaths.hpp"

SYCL_EXTERNAL vecType operator*=(vecType &a, vecType b) {
    a[0] *= b[0];
    a[1] *= b[1];
    return a;
}

SYCL_EXTERNAL vecType operator*(vecType a, vecType b) { return a *= b; }

SYCL_EXTERNAL vecType operator+=(vecType &a, vecType b) {
    a[0] += b[0];
    a[1] += b[1];
    return a;
}

SYCL_EXTERNAL vecType operator+(vecType a, vecType b) { return a += b; }

SYCL_EXTERNAL vecType operator-=(vecType &a, vecType b) {
    a[0] -= b[0];
    a[1] -= b[1];
    return a;
}

SYCL_EXTERNAL vecType operator-(vecType a, vecType b) { return a -= b; }

SYCL_EXTERNAL vecType operator*=(vecType &a, float s) {
    a[0] *= s;
    a[1] *= s;
    return a;
}

SYCL_EXTERNAL vecType operator*(vecType a, float s) { return a *= s; }

SYCL_EXTERNAL vecType operator*=(float s, vecType &a) {
    a[0] *= s;
    a[1] *= s;
    return a;
}

SYCL_EXTERNAL vecType operator*(float s, vecType a) { return a *= s; }

SYCL_EXTERNAL vecType operator/=(vecType &a, float s) {
    a[0] /= s;
    a[1] /= s;
    return a;
}

SYCL_EXTERNAL vecType operator/(vecType a, float s) { return a /= s; }
