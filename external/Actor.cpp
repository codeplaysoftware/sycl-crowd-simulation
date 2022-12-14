/***************************************************************************
 *
 *  Copyright (C) 2022 Codeplay Software Ltd.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  Codeplay's crowd-simulation
 *
 *  Actor.cpp
 *
 *  Description:
 *    Class denoting an actor in social force model
 *
 **************************************************************************/

#include "Actor.hpp"

Actor::Actor(sycl::float2 pPos, sycl::float2 pVelocity, float pDesiredSpeed,
             int pPathId, float pMass, float pRadius, bool pAtDestination,
             std::array<int, 3> pColor)
    : pos(pPos), velocity(pVelocity), desiredSpeed(pDesiredSpeed),
      pathId(pPathId), mass(pMass), radius(pRadius),
      atDestination(pAtDestination), color(pColor), destinationIndex(0),
      bBox({0, 0}) {}

SYCL_EXTERNAL sycl::float2 Actor::getPos() const { return pos; }

SYCL_EXTERNAL sycl::float2 Actor::getVelocity() const { return velocity; }

SYCL_EXTERNAL float Actor::getDesiredSpeed() const { return desiredSpeed; }

SYCL_EXTERNAL int Actor::getPathId() const { return pathId; }

SYCL_EXTERNAL int Actor::getDestinationIndex() const {
    return destinationIndex;
}

SYCL_EXTERNAL float Actor::getMass() const { return mass; }

SYCL_EXTERNAL float Actor::getRadius() const { return radius; }

SYCL_EXTERNAL bool Actor::getAtDestination() const { return atDestination; }

SYCL_EXTERNAL std::array<int, 3> Actor::getColor() const { return color; }

SYCL_EXTERNAL std::array<int, 2> Actor::getBBox() const { return bBox; }

SYCL_EXTERNAL uint Actor::getSeed() const { return seed; }

SYCL_EXTERNAL float Actor::getForce() const { return force; }

SYCL_EXTERNAL void Actor::setPos(sycl::float2 newPos) { pos = newPos; }

SYCL_EXTERNAL void Actor::setVelocity(sycl::float2 newVelocity) {
    velocity = newVelocity;
}

SYCL_EXTERNAL void Actor::setDesiredSpeed(float newDesiredSpeed) {
    desiredSpeed = newDesiredSpeed;
}

SYCL_EXTERNAL void Actor::setAtDestination(bool param) {
    atDestination = param;
}

SYCL_EXTERNAL void Actor::setColor(std::array<int, 3> newColor) {
    color = newColor;
}

SYCL_EXTERNAL void Actor::setBBox(std::array<int, 2> newBBox) {
    bBox = newBBox;
}

SYCL_EXTERNAL void Actor::setSeed(uint newSeed) { seed = newSeed; }

SYCL_EXTERNAL void Actor::setForce(float newForce) { force = newForce; }

SYCL_EXTERNAL void Actor::checkAtDestination(sycl::float4 destination,
                                             int pathSize) {
    // Destinations are defined as rectangular regions
    if (pos[0] >= destination[0] && pos[0] <= destination[2] &&
        pos[1] >= destination[1] && pos[1] <= destination[3]) {
        if (destinationIndex >= PATH_ALLOCATION_SIZE - 1 ||
            destinationIndex >= pathSize - 1) {
            this->setAtDestination(true);
        } else {
            destinationIndex++;
        }
    }
}
