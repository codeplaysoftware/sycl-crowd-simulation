#ifndef RandomNumber_hpp
#define RandomNumber_hpp

#include <sycl/sycl.hpp>

SYCL_EXTERNAL uint randXorShift(uint state) {
    state ^= (state << 13);
    state ^= (state >> 17);
    state ^= (state << 5);
    return state;
}

#endif
