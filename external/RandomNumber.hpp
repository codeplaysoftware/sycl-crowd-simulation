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
 *  RandomNumber.hpp
 *
 *  Description:
 *    Efficient random number generation on the GPU
 *
 **************************************************************************/

#ifndef RandomNumber_hpp
#define RandomNumber_hpp

#include <sycl/sycl.hpp>

SYCL_EXTERNAL uint randXorShift(uint state);

// Generate a random number in range -1 to 1
inline SYCL_EXTERNAL float rngMinusOneToOne(uint seed) {
    return (float(seed) * (2.0f / 4294967296.0f)) - 1.0f;
}

#endif
