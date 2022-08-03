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
 *  DifferentialEq.cpp
 *
 *  Description:
 *    Kernel for calculating social forces
 * 
 **************************************************************************/

#include "DifferentialEq.hpp"

SYCL_EXTERNAL void differentialEq(
    int actorIndex,
    sycl::accessor<Actor, 1, sycl::access::mode::read_write> actors,
    sycl::accessor<std::array<sycl::float2, 2>, 1, sycl::access::mode::read> walls,
    sycl::accessor<Path, 1, sycl::access::mode::read> paths, 
    sycl::accessor<bool, 1, sycl::access::mode::read> heatmapEnabled) {
    Actor *currentActor = &actors[actorIndex];

    sycl::float2 pos = currentActor->getPos();

    // Calculate personal impulse
    float mi = currentActor->getMass();
    float v0i = currentActor->getDesiredSpeed();
    std::array<sycl::float2, 2> destination =
        paths[currentActor->getPathId()]
            .getCheckpoints()[currentActor->getDestinationIndex()];

    // Find direction vector to nearest point in destination region
    std::pair<float, sycl::float2> minRegionDistance;
    std::array<sycl::float2, 4> destinationRect = {
        destination[0],
        {destination[1][0], destination[0][1]},
        destination[1],
        {destination[0][0], destination[1][1]}};
    for (int x = 0; x < 4; x++) {
        int endIndex = x == 3 ? 0 : x + 1;
        auto dniw =
            getDistanceAndNiw(currentActor->getPos(),
                              {destinationRect[x], destinationRect[endIndex]});
        if (dniw.first < minRegionDistance.first ||
            minRegionDistance.first == 0) {
            minRegionDistance = dniw;
        }
    }
    minRegionDistance.second = normalize(minRegionDistance.second);
    sycl::float2 e0i = {-minRegionDistance.second[0], -minRegionDistance.second[1]};

    sycl::float2 vi = currentActor->getVelocity();

    sycl::float2 personalImpulse = mi * (((v0i * e0i) - vi) / Ti);

    // Collect neighbouring bounding boxes
    std::array<int, 2> currentBBox = currentActor->getBBox();
    std::array<std::array<int, 2>, 9> neighbourBoxes = {{
        {currentBBox},
        {currentBBox[0] - 1, currentBBox[1] - 1},
        {currentBBox[0] - 1, currentBBox[1]},
        {currentBBox[0] - 1, currentBBox[1] + 1},
        {currentBBox[0], currentBBox[1] + 1},
        {currentBBox[0], currentBBox[1] - 1},
        {currentBBox[0] + 1, currentBBox[1] - 1},
        {currentBBox[0] + 1, currentBBox[1]},
        {currentBBox[0] + 1, currentBBox[1] + 1},
    }};

    // Calculate forces applied by neighbouring actors (in valid bounding boxes)
    sycl::float2 peopleForces = {0, 0};
    for (int x = 0; x < actors.size(); x++) {
        Actor neighbour = actors[x];

        bool bBoxFlag =
            std::any_of(neighbourBoxes.begin(), neighbourBoxes.end(),
                        [neighbour](std::array<int, 2> i) {
                            return i[0] == neighbour.getBBox()[0] &&
                                   i[1] == neighbour.getBBox()[1];
                        });

        if (actorIndex != x && !neighbour.getAtDestination() && bBoxFlag) {
            sycl::float2 currentToNeighbour = pos - neighbour.getPos();
            float dij = magnitude(currentToNeighbour);
            float rij = neighbour.getRadius() + currentActor->getRadius();
            sycl::float2 nij = currentToNeighbour / dij;
            sycl::float2 tij = getTangentialVector(nij);
            float g = dij > rij ? 0 : rij - dij;
            float deltavtij = dotProduct(
                (neighbour.getVelocity() - currentActor->getVelocity()), tij);

            peopleForces +=
                (PEOPLEAi * sycl::exp((rij - dij) / Bi) + K1 * g) * nij +
                (K2 * g * deltavtij * tij);
        }
    }

    // Calculate forces applied by walls
    sycl::float2 wallForces = {0, 0};
    for (int x = 0; x < walls.size(); x++) {
        std::array<sycl::float2, 2> currentWall = walls[x];
        float ri = currentActor->getRadius();
        std::pair<float, sycl::float2> dAndn = getDistanceAndNiw(pos, currentWall);
        float diw = dAndn.first;
        float g = diw > ri ? 0 : ri - diw;
        sycl::float2 niw = normalize(dAndn.second);
        sycl::float2 tiw = getTangentialVector(niw);

        wallForces += (WALLAi * sycl::exp((ri - diw) / Bi) + K1 * g) * niw -
                      (K2 * g * dotProduct(vi, tiw) * tiw);
    }

    sycl::float2 forceSum = personalImpulse + peopleForces + wallForces;

#ifdef STATS
    if (!currentActor->getAtDestination()) {
        currentActor->setForce(magnitude(forceSum));
    }
#endif

    // Apply random force variations
    float seed = currentActor->getSeed();
    float randX = rngMinusOneToOne(seed);
    float randY = rngMinusOneToOne(randXorShift(seed));
    forceSum += {randX, randY};
    currentActor->setSeed(randXorShift(seed));

    // Color actor according to heatmap
    if (heatmapEnabled[0]) {
        // theoreticalMax was decided based on observed max forces for a set of
        // configurations It may need to be altered based on the max forces of
        // your config to create a satisfying heatmap
        float theoreticalMax = 700.0f;
        auto colorVal =
            sycl::fabs((forceSum[0] + forceSum[1]) / theoreticalMax);
        if (colorVal > 1) {
            colorVal = 1.0f;
        }
        auto color = findColor(colorVal);
        currentActor->setColor({int(color[0]), int(color[1]), int(color[2])});
    }

    // Perform integration
    sycl::float2 acceleration = forceSum / mi;
    currentActor->setVelocity(vi + acceleration * TIMESTEP);
    currentActor->setPos(pos + currentActor->getVelocity() * TIMESTEP);

    currentActor->checkAtDestination(
        destination, paths[currentActor->getPathId()].getPathSize());
}
