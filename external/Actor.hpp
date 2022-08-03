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
 *  Actor.hpp
 *
 *  Description:
 *    Class denoting an actor in social force model
 *
 **************************************************************************/

#ifndef Actor_hpp
#define Actor_hpp

#include "Path.hpp"
#include "RandomNumber.hpp"
#include <array>
#include <iostream>
#include <random>
#include <sycl/sycl.hpp>
#include <vector>

class Actor {
  private:
    std::array<int, 3> color;
    sycl::float2 pos;
    sycl::float2 velocity;
    std::array<int, 2> bBox;
    float desiredSpeed;
    int pathId;
    int destinationIndex;
    float mass;
    float radius;
    uint seed;
    float force;
    bool atDestination;

  public:
    Actor(sycl::float2 pPos, sycl::float2 pVelocity, float pdesiredSpeed,
          int pPathId, float pMass, float pRadius, bool pAtDestination,
          std::array<int, 3> pColor);

    SYCL_EXTERNAL sycl::float2 getPos() const;
    SYCL_EXTERNAL sycl::float2 getVelocity() const;
    SYCL_EXTERNAL float getDesiredSpeed() const;
    SYCL_EXTERNAL int getPathId() const;
    SYCL_EXTERNAL int getDestinationIndex() const;
    SYCL_EXTERNAL float getMass() const;
    SYCL_EXTERNAL float getRadius() const;
    SYCL_EXTERNAL bool getAtDestination() const;
    SYCL_EXTERNAL std::array<int, 3> getColor() const;
    SYCL_EXTERNAL std::array<int, 2> getBBox() const;
    SYCL_EXTERNAL uint getSeed() const;
    SYCL_EXTERNAL float getForce() const;

    SYCL_EXTERNAL void setPos(sycl::float2 newPos);
    SYCL_EXTERNAL void setVelocity(sycl::float2 newVelocity);
    SYCL_EXTERNAL void setDesiredSpeed(float newDesiredSpeed);
    SYCL_EXTERNAL void setAtDestination(bool param);
    SYCL_EXTERNAL void setColor(std::array<int, 3> newColor);
    SYCL_EXTERNAL void setBBox(std::array<int, 2> newBBox);
    SYCL_EXTERNAL void setSeed(uint newSeed);
    SYCL_EXTERNAL void setForce(float newForce);

    SYCL_EXTERNAL void
    checkAtDestination(std::array<sycl::float2, 2> destination, int pathSize);
};

#endif
