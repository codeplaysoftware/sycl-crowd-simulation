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