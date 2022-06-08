#include "Actor.hpp"
#include <iostream>
#include <array>
using namespace std;

Actor::Actor(array<float, 2> pPos, array<float, 2> pVelocity, array<float, 2> pDesiredVelocity, float pMass, float pRadius) {
    pos = pPos;
    velocity = pVelocity;
    desiredVelocity = pDesiredVelocity;
    mass = pMass;
    radius = pRadius;
}