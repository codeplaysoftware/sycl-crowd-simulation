#include "Actor.hpp"
#include <iostream>
#include <array>

Actor::Actor(std::array<float, 2> pPos, std::array<float, 2> pVelocity, std::array<float, 2> pDesiredVelocity, std::array<float, 2> pDestination, float pMass, float pRadius) {
    pos = pPos;
    velocity = pVelocity;
    desiredVelocity = pDesiredVelocity;
    destination = pDestination;
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

std::array<float, 2> Actor::getDestination() {
    return destination;
}

float Actor::getMass() {
    return mass;
}

float Actor::getRadius() {
    return radius;
}

void Actor::setPos(std::array<float, 2> newPos) {
    pos = newPos;
}

void Actor::setVelocity(std::array<float, 2> newVelocity) {
    velocity = newVelocity;
}

void Actor::setDesiredVelocity(std::array<float, 2> newDesiredVelocity) {
    desiredVelocity = newDesiredVelocity;
}

void Actor::setDestination(std::array<float, 2> newDestination) {
    destination = newDestination;
}