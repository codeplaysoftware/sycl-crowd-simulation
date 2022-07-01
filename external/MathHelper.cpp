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
    return sycl::sqrt((inp[0] * inp[0]) + (inp[1] * inp[1]));
}

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

SYCL_EXTERNAL vecType getDestination(vecType pos, std::array<vecType, 4> region) {
    std::pair<float, vecType> distanceVectorPair;
    for (int x = 0; x < 4; x++) {
        int endIndex = x == 3 ? 0 : x + 1;

        vecType AB = getDirectionVector(region[x], region[endIndex]);
        vecType BP = getDirectionVector(region[endIndex], pos);
        vecType AP = getDirectionVector(region[x], pos);

        float ABdotBP = dotProduct(AB, BP);
        float ABdotAP = dotProduct(AB, AP);

        if (ABdotBP >= 0) {
            if (distance(pos, region[endIndex]) < distanceVectorPair.first || distanceVectorPair.first == 0) {
                distanceVectorPair.first = distance(pos, region[endIndex]);
                distanceVectorPair.second = getDirectionVector(pos, region[endIndex]);
            }
        }
        else if (ABdotAP < 0) {
            if (distance(pos, region[x]) < distanceVectorPair.first || distanceVectorPair.first == 0) {
                distanceVectorPair.first = distance(pos, region[x]);
                distanceVectorPair.second = getDirectionVector(pos, region[x]);
            }
        }
        else {
            float lSquared = dotProduct(AB, AB);
            if (lSquared != 0.0) {
                float t = sycl::max(0.0f, sycl::min(1.0f, dotProduct(AP, AB) / lSquared));
                auto projection = t * AB;

                if (distance(AP, projection) < distanceVectorPair.first || distanceVectorPair.first == 0) {
                    distanceVectorPair.first = distance(AP, projection);
                    vecType forSwitching = AP - projection;
                    forSwitching[0] = -forSwitching[0];
                    forSwitching[1] = -forSwitching[1];
                    distanceVectorPair.second = forSwitching;
                }
            }
        }
    }

    return normalize(distanceVectorPair.second);
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
        float t = sycl::max(0.0f, sycl::min(1.0f, dotProduct(AP, AB) / lSquared));
        auto projection = t * AB;
        
        return {distance(AP, projection), normalize(AP - projection)};
    }
}

SYCL_EXTERNAL vecType getTangentialVector(vecType normal) {
    return {-normal[1], normal[0]};
}
