#include "RandomNumber.hpp"

// xorshift RNG developed by George Marsaglia [https://www.jstatsoft.org/article/download/v008i14/916]
SYCL_EXTERNAL uint randXorShift(uint state) {
    state ^= (state << 13);
    state ^= (state >> 17);
    state ^= (state << 5);
    return state;
}
