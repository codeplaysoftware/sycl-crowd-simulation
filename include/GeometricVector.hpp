#ifndef GeometricVector_hpp
#define GeometricVector_hpp

#include <iostream>
#include <cmath>
#include <array>
#include <sycl/sycl.hpp>

class GeometricVector {
private:
    std::array<float, 2> contents;
public:
    GeometricVector();
    GeometricVector(std::array<float, 2> pContents);

    SYCL_EXTERNAL float& operator[](int index);
    SYCL_EXTERNAL void operator=(std::array<float, 2> newContents);
};

SYCL_EXTERNAL GeometricVector operator*=(GeometricVector& a, GeometricVector b);
SYCL_EXTERNAL GeometricVector operator*(GeometricVector a, GeometricVector b);

SYCL_EXTERNAL GeometricVector operator+=(GeometricVector& a, GeometricVector b);
SYCL_EXTERNAL GeometricVector operator+(GeometricVector a, GeometricVector b);

SYCL_EXTERNAL GeometricVector operator-=(GeometricVector& a, GeometricVector b);
SYCL_EXTERNAL GeometricVector operator-(GeometricVector a, GeometricVector b);

SYCL_EXTERNAL GeometricVector operator*=(GeometricVector& a, float s);
SYCL_EXTERNAL GeometricVector operator*(GeometricVector a, float s);
SYCL_EXTERNAL GeometricVector operator*=(float s, GeometricVector& a);
SYCL_EXTERNAL GeometricVector operator*(float s, GeometricVector a);

#endif
