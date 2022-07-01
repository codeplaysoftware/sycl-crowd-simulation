#include "DifferentialEq.hpp"

SYCL_EXTERNAL void differentialEq(int currentIndex, sycl::accessor<Actor, 1, sycl::access::mode::read_write> actors, sycl::accessor<std::array<vecType, 2>, 1, sycl::access::mode::read> walls, sycl::accessor<Path, 1, sycl::access::mode::read> paths, sycl::stream out) {
    Actor* currentActor = &actors[currentIndex];

    vecType pos = currentActor->getPos();

    // Calculate personal impulse
    float mi = currentActor->getMass();
    float v0i = currentActor->getDesiredSpeed();
    std::array<vecType, 4> destination = paths[currentActor->getPathId()].getCheckpoints()[currentActor->getDestinationIndex()];
    
    vecType e0i = getDestination(currentActor->getPos(), destination);
    
    //vecType e0i = normalize(getDirectionVector(currentActor->getPos(), destination));
    vecType vi = currentActor->getVelocity();

    vecType personalImpulse = mi * (((v0i * e0i) - vi) / Ti);
    
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

    // Calculate forces applied by neighbouring actors
    vecType peopleForces = {0, 0};
    for (int x = 0; x < actors.size(); x++) {
        Actor neighbour = actors[x];
        
        bool bBoxFlag = std::any_of(neighbourBoxes.begin(), neighbourBoxes.end(), [neighbour](std::array<int, 2> i){
            return i[0] == neighbour.getBBox()[0] && i[1] == neighbour.getBBox()[1];
        });
        
        if (currentIndex != x && !neighbour.getAtDestination() && bBoxFlag) {
            vecType currentToNeighbour = pos - neighbour.getPos();
            float dij = magnitude(currentToNeighbour);
            float rij = neighbour.getRadius() + currentActor->getRadius();
            vecType nij = (currentToNeighbour) / dij;
            vecType tij = getTangentialVector(nij);
            float g = dij > rij ? 0 : rij - dij;
            float deltavtij = dotProduct((neighbour.getVelocity() - currentActor->getVelocity()), tij);

            peopleForces += (PEOPLEAi * sycl::exp((rij - dij) / Bi) + K1 * g) * nij + (K2 * g * deltavtij * tij);
        }
    }

    // Calculate forces applied by walls
    vecType wallForces = {0, 0};
    for (int x = 0; x < walls.size(); x++) {
        std::array<vecType, 2> currentWall = walls[x];
        float ri = currentActor->getRadius();
        std::pair<float, vecType> dAndn = getDistanceAndNiw(pos, currentWall);
        float diw = dAndn.first;
        float g = diw > ri ? 0 : ri - diw;
        vecType niw = dAndn.second;
        vecType tiw = getTangentialVector(niw);

        wallForces += (WALLAi * sycl::exp((ri - diw) / Bi) + K1 * g) * niw - (K2 * g * dotProduct(vi, tiw) * tiw);
    }

    vecType forceSum = personalImpulse + peopleForces + wallForces;

    // Apply random force variations
    forceSum += currentActor->getVariation();

    // Color actor according to heatmap
    if (currentActor->getHeatmapEnabled()) {
        auto colorVal = sycl::fabs((forceSum[0] + forceSum[1]) / 700.0f);
        if (colorVal > 1) { colorVal = 1.0f; }
        auto color = findColor(colorVal);
        currentActor->setColor({int(color[0]), int(color[1]), int(color[2])});
    }

    // out << "People Forces: (" << peopleForces[0] << ", " << peopleForces[1] << ")    " << z << sycl::endl;
    // out << "Wall Forces: (" << wallForces[0] << ", " << wallForces[1] << ")    " << z << sycl::endl;
    // out << "Acceleration: (" << acceleration[0] << ", " << acceleration[1] << ")    " << z << sycl::endl;
    // out << "-----------------------" << sycl::endl;

    vecType acceleration = forceSum / mi;
    currentActor->setVelocity(vi + acceleration * TIMESTEP);
    currentActor->setPos(pos + currentActor->getVelocity() * TIMESTEP);

    currentActor->checkAtDestination(destination, paths[currentActor->getPathId()].getPathSize());
}
