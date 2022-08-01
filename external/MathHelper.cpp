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
 *  MathHelper.cpp
 *
 *  Description:
 *    Collection of helper functions performing common vector math 
 *    operations
 * 
 **************************************************************************/

#include "MathHelper.hpp"

SYCL_EXTERNAL vecType getDirectionVector(vecType from, vecType to) {
    return to - from;
}

SYCL_EXTERNAL vecType velFromSpeedAndDir(float speed, vecType direction) {
    return direction * (speed * inverseMagnitude(direction));
}

SYCL_EXTERNAL vecType velToPoint(float speed, vecType pos,
                                 vecType destination) {
    return velFromSpeedAndDir(speed, getDirectionVector(pos, destination));
}

SYCL_EXTERNAL float magnitude(vecType inp) {
    return sycl::sqrt((inp[0] * inp[0]) + (inp[1] * inp[1]));
}

// Fast inverse square root optimisation
// https://en.wikipedia.org/wiki/Fast_inverse_square_root
SYCL_EXTERNAL float inverseMagnitude(vecType inp) {
    return sycl::rsqrt((inp[0] * inp[0]) + (inp[1] * inp[1]));
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

// Returns pair of distance to line and normalised direction from wall to point
SYCL_EXTERNAL std::pair<float, vecType>
getDistanceAndNiw(vecType point, std::array<vecType, 2> wall) {
    vecType AB = getDirectionVector(wall[0], wall[1]);
    vecType BP = getDirectionVector(wall[1], point);
    vecType AP = getDirectionVector(wall[0], point);

    float ABdotBP = dotProduct(AB, BP);
    float ABdotAP = dotProduct(AB, AP);

    if (ABdotBP >= 0) {
        return {distance(point, wall[1]), BP};
    } else if (ABdotAP < 0) {
        return {distance(point, wall[0]), AP};
    } else {
        float lSquared = dotProduct(AB, AB);
        if (lSquared == 0.0) {
            return {0, {0, 0}};
        }
        float t =
            sycl::max(0.0f, sycl::min(1.0f, dotProduct(AP, AB) / lSquared));
        auto projection = t * AB;

        return {distance(AP, projection), AP - projection};
    }
}

SYCL_EXTERNAL vecType getTangentialVector(vecType normal) {
    return {-normal[1], normal[0]};
}
