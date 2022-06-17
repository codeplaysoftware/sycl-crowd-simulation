#include "Actor.hpp"
#include <iostream>
#include <array>
#include <sycl/sycl.hpp>

Actor::Actor(vecType pPos, vecType pVelocity, vecType pDesiredVelocity, vecType pDestination, float pMass, float pRadius, bool pAtDestination, std::array<int, 3> pColor) {
    pos = pPos;
    velocity = pVelocity;
    desiredVelocity = pDesiredVelocity;
    destination = pDestination;
    mass = pMass;
    radius = pRadius;
    atDestination = pAtDestination;
    color = pColor;
}

SYCL_EXTERNAL vecType Actor::getPos() {
    return pos;
}

SYCL_EXTERNAL vecType Actor::getVelocity() {
    return velocity;
}

SYCL_EXTERNAL vecType Actor::getDesiredVelocity() {
    return desiredVelocity;
}

SYCL_EXTERNAL vecType Actor::getDestination() {
    return destination;
}

SYCL_EXTERNAL float Actor::getMass() {
    return mass;
}

SYCL_EXTERNAL float Actor::getRadius() {
    return radius;
}

SYCL_EXTERNAL bool Actor::getAtDestination() {
    return atDestination;
}

SYCL_EXTERNAL std::array<int, 3> Actor::getColor() {
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
