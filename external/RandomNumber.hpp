#ifndef RandomNumber_hpp
#define RandomNumber_hpp

#include <sycl/sycl.hpp>

SYCL_EXTERNAL uint randXorShift(uint state);

// Generate a random number in range -1 to 1
inline SYCL_EXTERNAL float rngMinusOneToOne(uint seed) {
    return (float(seed) * (2.0f / 4294967296.0f)) - 1.0f;
}

#endif
