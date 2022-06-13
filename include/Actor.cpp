#include "Actor.hpp"
#include <iostream>
#include <array>
#include <sycl/sycl.hpp>

Actor::Actor(std::array<float, 2> pPos, std::array<float, 2> pVelocity, std::array<float, 2> pDesiredVelocity, std::array<float, 2> pDestination, float pMass, float pRadius) {
    pos = pPos;
    velocity = pVelocity;
    desiredVelocity = pDesiredVelocity;
    destination = pDestination;
    mass = pMass;
    radius = pRadius;
}

SYCL_EXTERNAL std::array<float, 2> Actor::getPos() {
    return pos;
}

SYCL_EXTERNAL std::array<float, 2> Actor::getVelocity() {
    return velocity;
}

SYCL_EXTERNAL std::array<float, 2> Actor::getDesiredVelocity() {
    return desiredVelocity;
}

SYCL_EXTERNAL std::array<float, 2> Actor::getDestination() {
    return destination;
}

SYCL_EXTERNAL float Actor::getMass() {
    return mass;
}

SYCL_EXTERNAL float Actor::getRadius() {
    return radius;
}

SYCL_EXTERNAL void Actor::setPos(std::array<float, 2> newPos) {
    pos = newPos;
}

SYCL_EXTERNAL void Actor::setVelocity(std::array<float, 2> newVelocity) {
    velocity = newVelocity;
}

SYCL_EXTERNAL void Actor::setDesiredVelocity(std::array<float, 2> newDesiredVelocity) {
    desiredVelocity = newDesiredVelocity;
}

SYCL_EXTERNAL void Actor::setDestination(std::array<float, 2> newDestination) {
    destination = newDestination;
}
