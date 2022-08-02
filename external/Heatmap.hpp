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
 *  Heatmap.hpp
 *
 *  Description:
 *    Applying heatmap across actors reflecting how much force they are
 *    experiencing
 * 
 **************************************************************************/

#ifndef Heatmap_hpp
#define Heatmap_hpp

#include <array>
#include <iostream>
#include <sycl/sycl.hpp>

SYCL_EXTERNAL std::array<float, 3> HSVtoRGB(float h, float s, float v);

SYCL_EXTERNAL std::array<float, 3> findColor(float val);

#endif
