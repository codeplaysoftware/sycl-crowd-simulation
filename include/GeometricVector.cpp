#include <iostream>
#include <cmath>
#include <sycl/sycl.hpp>
#include <array>
#include "GeometricVector.hpp"

GeometricVector::GeometricVector() {
    contents = {0, 0};
}

GeometricVector::GeometricVector(std::array<float, 2> pContents) {
    contents = pContents;
}

SYCL_EXTERNAL float& GeometricVector::operator[](int index) {
    return contents[index];
}

SYCL_EXTERNAL void GeometricVector::operator=(std::array<float, 2> newContents) {
    contents = newContents;
}

SYCL_EXTERNAL GeometricVector operator*=(GeometricVector& a, GeometricVector b) {
    a[0] *= b[0];
    a[1] *= b[1];
    return a;
}

SYCL_EXTERNAL GeometricVector operator*(GeometricVector a, GeometricVector b) {
    return a *= b;
}

SYCL_EXTERNAL GeometricVector operator+=(GeometricVector& a, GeometricVector b) {
    a[0] += b[0];
    a[1] += b[1];
    return a;
}

SYCL_EXTERNAL GeometricVector operator+(GeometricVector a, GeometricVector b) {
    return a += b;
}

SYCL_EXTERNAL GeometricVector operator-=(GeometricVector& a, GeometricVector b) {
    a[0] -= b[0];
    a[1] -= b[1];
    return a;
}

SYCL_EXTERNAL GeometricVector operator-(GeometricVector a, GeometricVector b) {
    return a -= b;
}

SYCL_EXTERNAL GeometricVector operator*=(GeometricVector& a, float s) {
    a[0] *= s;
    a[1] *= s;
    return a;
}

SYCL_EXTERNAL GeometricVector operator*(GeometricVector a, float s) {
    return a *= s;
}

SYCL_EXTERNAL GeometricVector operator*=(float s, GeometricVector& a) {
    a[0] *= s;
    a[1] *= s;
    return a;
}

SYCL_EXTERNAL GeometricVector operator*(float s, GeometricVector a) {
    return a *= s;
}

SYCL_EXTERNAL GeometricVector operator/=(GeometricVector& a, float s) {
    a[0] /= s;
    a[1] /= s;
    return a;
}

SYCL_EXTERNAL GeometricVector operator/(GeometricVector a, float s) {
    return a *= s;
}
