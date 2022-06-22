#include "Actor.hpp"

Actor::Actor(vecType pPos, vecType pVelocity, float pDesiredSpeed, std::array<vecType, PATHALLOCATIONSIZE> pPath, int pPathSize, float pMass, float pRadius, bool pAtDestination, std::array<int, 3> pColor):
    pos(pPos), velocity(pVelocity), desiredSpeed(pDesiredSpeed),
    path(pPath), pathSize(pPathSize), mass(pMass), radius(pRadius), 
    atDestination(pAtDestination), color(pColor) {
        variation = {0, 0};
        destinationIndex = 0;
    }

SYCL_EXTERNAL vecType Actor::getPos() const {
    return pos;
}

SYCL_EXTERNAL vecType Actor::getVelocity() const {
    return velocity;
}

SYCL_EXTERNAL float Actor::getDesiredSpeed() const {
    return desiredSpeed;
}

SYCL_EXTERNAL std::array<vecType, PATHALLOCATIONSIZE> Actor::getPath() const {
    return path;
}

SYCL_EXTERNAL vecType Actor::getDestination() const {
    return path[destinationIndex];
}

SYCL_EXTERNAL vecType Actor::getVariation() const {
    return variation;
}

SYCL_EXTERNAL float Actor::getMass() const {
    return mass;
}

SYCL_EXTERNAL float Actor::getRadius() const {
    return radius;
}

SYCL_EXTERNAL bool Actor::getAtDestination() const {
    return atDestination;
}

SYCL_EXTERNAL std::array<int, 3> Actor::getColor() const {
    return color;
}

SYCL_EXTERNAL void Actor::setPos(vecType newPos) {
    pos = newPos;
}

SYCL_EXTERNAL void Actor::setVelocity(vecType newVelocity) {
    velocity = newVelocity;
}

SYCL_EXTERNAL void Actor::setDesiredSpeed(float newDesiredSpeed) {
    desiredSpeed = newDesiredSpeed;
}

SYCL_EXTERNAL void Actor::setPath(std::array<vecType, PATHALLOCATIONSIZE> newPath) {
    path = newPath;
}

SYCL_EXTERNAL void Actor::setVariation(vecType newVariation) {
    variation = newVariation;
}

SYCL_EXTERNAL void Actor::setAtDestination(bool param) {
    atDestination = param;
}

SYCL_EXTERNAL void Actor::setColor(std::array<int, 3> newColor) {
    color = newColor;
}

SYCL_EXTERNAL void Actor::checkAtDestination() {
    std::array<float, 4> destinationBoundingBox = {path[destinationIndex][0] + 0.2f, 
                                                   path[destinationIndex][0] - 0.2f,
                                                   path[destinationIndex][1] + 0.2f, 
                                                   path[destinationIndex][1] - 0.2f};
    if (pos[0] <= destinationBoundingBox[0] && pos[0] >= destinationBoundingBox[1]
        && pos[1] <= destinationBoundingBox[2] && pos[1] >= destinationBoundingBox[3]) {
            if (destinationIndex >= PATHALLOCATIONSIZE - 1 || destinationIndex >= pathSize - 1) {
                this->setAtDestination(true);
            }
            else {
                destinationIndex++;
            }
        }
}

void Actor::refreshVariation() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> distr{0.0f, 1.0f};
    this->setVariation({distr(gen), distr(gen)});
}
