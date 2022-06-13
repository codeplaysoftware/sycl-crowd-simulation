#include <iostream>
#include <vector>
#include <array>
#include <sycl.hpp>
#include "DifferentialEq.hpp"
#include "Actor.hpp"
#include "Room.hpp"
#include "MathHelper.hpp"

SYCL_EXTERNAL void personalImpulse(Actor &actor) {
    auto mass = actor.getMass();
    auto desiredSpeed = 1.5;
    auto desiredDirection = getDirectionVector(actor.getPos(), actor.getDestination());
    auto actualVelocity = actor.getVelocity();

    //return ((desiredSpeed * desiredDirection) - actualVelocity) / ti
};
