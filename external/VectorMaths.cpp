#include <iostream>
#include <cmath>
#include <sycl/sycl.hpp>
#include <array>
#include "VectorMaths.hpp"

SYCL_EXTERNAL vecType operator*=(vecType& a, vecType b) {
    a[0] *= b[0];
    a[1] *= b[1];
    return a;
}

SYCL_EXTERNAL vecType operator*(vecType a, vecType b) {
    return a *= b;
}

SYCL_EXTERNAL vecType operator+=(vecType& a, vecType b) {
    a[0] += b[0];
    a[1] += b[1];
    return a;
}

SYCL_EXTERNAL vecType operator+(vecType a, vecType b) {
    return a += b;
}

SYCL_EXTERNAL vecType operator-=(vecType& a, vecType b) {
    a[0] -= b[0];
    a[1] -= b[1];
    return a;
}

SYCL_EXTERNAL vecType operator-(vecType a, vecType b) {
    return a -= b;
}

SYCL_EXTERNAL vecType operator*=(vecType& a, float s) {
    a[0] *= s;
    a[1] *= s;
    return a;
}

SYCL_EXTERNAL vecType operator*(vecType a, float s) {
    return a *= s;
}

SYCL_EXTERNAL vecType operator*=(float s, vecType& a) {
    a[0] *= s;
    a[1] *= s;
    return a;
}

SYCL_EXTERNAL vecType operator*(float s, vecType a) {
    return a *= s;
}

SYCL_EXTERNAL vecType operator/=(vecType& a, float s) {
    a[0] /= float(s);
    a[1] /= float(s);
    return a;
}

SYCL_EXTERNAL vecType operator/(vecType a, float s) {
    return a /= s;
}
