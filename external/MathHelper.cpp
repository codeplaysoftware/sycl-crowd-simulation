#include "MathHelper.hpp"

SYCL_EXTERNAL vecType getDirectionVector(vecType from, vecType to) {
    return to - from;
}

SYCL_EXTERNAL vecType velFromSpeedAndDir(float speed, vecType direction) {
    return direction * (speed * inverseMagnitude(direction));
}

SYCL_EXTERNAL vecType velToPoint(float speed, vecType pos, vecType destination) {
    return velFromSpeedAndDir(speed, getDirectionVector(pos, destination));
}

SYCL_EXTERNAL float magnitude(vecType inp) {
    return std::sqrt((inp[0] * inp[0]) + (inp[1] * inp[1]));
}

SYCL_EXTERNAL float inverseMagnitude(vecType inp) {
    float x = (inp[0] * inp[0]) + (inp[1] * inp[1]);
    float y = x;
    uint32_t *i = reinterpret_cast<uint32_t *>(&y);
    const uint32_t expMask = 0x7F800000;
    const uint32_t magicNumber = 0x5F000000;
    *i = magicNumber - ((*i >> 1) & expMask);
    return (x * y * y + 1) / (2 * x * y);
}

SYCL_EXTERNAL float dotProduct(vecType a, vecType b) {
    return (a[0] * b[0]) + (a[1] * b[1]);
}

SYCL_EXTERNAL float distance(vecType from, vecType to) {
    return magnitude(from - to);
}

SYCL_EXTERNAL vecType normalize(vecType inp) {
    return inp * inverseMagnitude(inp);
}

SYCL_EXTERNAL std::pair<float, vecType> getDistanceAndNiw(vecType point, std::array<vecType, 2> wall) {
    vecType AB = getDirectionVector(wall[0], wall[1]);
    vecType BP = getDirectionVector(wall[1], point);
    vecType AP = getDirectionVector(wall[0], point);

    float ABdotBP = dotProduct(AB, BP);
    float ABdotAP = dotProduct(AB, AP);

    if (ABdotBP >= 0) {
        return {distance(point, wall[1]), normalize(BP)};
    }
    else if (ABdotAP < 0) {
        return {distance(point, wall[0]), normalize(AP)};
    }
    else {
        // float lSquared = pow(magnitude(AB), 2);
        float lSquared = dotProduct(AB, AB);
        if (lSquared == 0.0) {
            return {0, {0, 0}};
        }
        float t = std::max(0.0f, std::min(1.0f, dotProduct(AP, AB) / lSquared));
        auto projection = t * AB;
        
        return {distance(AP, projection), normalize(AP - projection)};
    }
}
