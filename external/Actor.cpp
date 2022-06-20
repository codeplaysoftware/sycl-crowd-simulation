#include "Actor.hpp"

Actor::Actor(vecType pPos, vecType pVelocity, vecType pDesiredVelocity, vecType pDestination, float pMass, float pRadius, bool pAtDestination, std::array<int, 3> pColor):
    pos(pPos), velocity(pVelocity), desiredVelocity(pDesiredVelocity),
    destination(pDestination), mass(pMass), radius(pRadius), atDestination(pAtDestination),
    color(pColor) {}

SYCL_EXTERNAL vecType Actor::getPos() const {
    return pos;
}

SYCL_EXTERNAL vecType Actor::getVelocity() const {
    return velocity;
}

SYCL_EXTERNAL vecType Actor::getDesiredVelocity() const {
    return desiredVelocity;
}

SYCL_EXTERNAL vecType Actor::getDestination() const {
    return destination;
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

SYCL_EXTERNAL void Actor::setDesiredVelocity(vecType newDesiredVelocity) {
    desiredVelocity = newDesiredVelocity;
}

SYCL_EXTERNAL void Actor::setDestination(vecType newDestination) {
    destination = newDestination;
}

SYCL_EXTERNAL void Actor::setAtDestination(bool param) {
    atDestination = param;
}

SYCL_EXTERNAL void Actor::checkAtDestination() {
    std::array<float, 4> destinationBoundingBox = {destination[0] + 0.01f, destination[0] - 0.01f, destination[1] + 0.01f, destination[1] - 0.01f};
    if (pos[0] <= destinationBoundingBox[0] && pos[0] >= destinationBoundingBox[1]
        && pos[1] <= destinationBoundingBox[2] && pos[1] >= destinationBoundingBox[3]) {
            this->setAtDestination(true);
        }
}
