#include "Actor.hpp"
#include <iostream>
#include <array>

Actor::Actor(std::array<float, 2> pPos, std::array<float, 2> pVelocity, std::array<float, 2> pDesiredVelocity, float pMass, float pRadius) {
    pos = pPos;
    velocity = pVelocity;
    desiredVelocity = pDesiredVelocity;
    mass = pMass;
    radius = pRadius;
}

std::array<float, 2> Actor::getPos() {
    return pos;
}

std::array<float, 2> Actor::getVelocity() {
    return velocity;
}

std::array<float, 2> Actor::getDesiredVelocity() {
    return desiredVelocity;
}

float Actor::getMass() {
    return mass;
}

float Actor::getRadius() {
    return radius;
}
