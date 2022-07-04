#ifndef Heatmap_hpp
#define Heatmap_hpp

#include <array>
#include <iostream>
#include <sycl/sycl.hpp>
#include <vector>

SYCL_EXTERNAL std::array<float, 3> HSVtoRGB(float h, float s, float v);

SYCL_EXTERNAL std::array<float, 3> findColor(float val);

#endif
