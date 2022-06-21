#ifndef Heatmap_hpp
#define Heatmap_hpp

#include <iostream>
#include <array>
#include <vector>
#include <sycl/sycl.hpp>

SYCL_EXTERNAL std::array<float, 3> HSVtoRGB(float h, float s, float v);

SYCL_EXTERNAL std::array<float, 3> findColor(float val);

#endif
