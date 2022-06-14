#include "Actor.hpp"
#include <iostream>
#include <array>
#include <sycl/sycl.hpp>

Actor::Actor(GeometricVector pPos, GeometricVector pVelocity, GeometricVector pDesiredVelocity, GeometricVector pDestination, float pMass, float pRadius) {
    pos = pPos;
    velocity = pVelocity;
    desiredVelocity = pDesiredVelocity;
    destination = pDestination;
    mass = pMass;
    radius = pRadius;
}

SYCL_EXTERNAL GeometricVector Actor::getPos() {
    return pos;
}

SYCL_EXTERNAL GeometricVector Actor::getVelocity() {
    return velocity;
}

SYCL_EXTERNAL GeometricVector Actor::getDesiredVelocity() {
    return desiredVelocity;
}

SYCL_EXTERNAL GeometricVector Actor::getDestination() {
    return destination;
}

SYCL_EXTERNAL float Actor::getMass() {
    return mass;
}

SYCL_EXTERNAL float Actor::getRadius() {
    return radius;
}

SYCL_EXTERNAL void Actor::setPos(GeometricVector newPos) {
    pos = newPos;
}

SYCL_EXTERNAL void Actor::setVelocity(GeometricVector newVelocity) {
    velocity = newVelocity;
}

SYCL_EXTERNAL void Actor::setDesiredVelocity(GeometricVector newDesiredVelocity) {
    desiredVelocity = newDesiredVelocity;
}

SYCL_EXTERNAL void Actor::setDestination(GeometricVector newDestination) {
    destination = newDestination;
}
