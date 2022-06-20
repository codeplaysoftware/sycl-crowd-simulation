#include "DifferentialEq.hpp"

SYCL_EXTERNAL void differentialEq(int currentIndex, sycl::accessor<Actor, 1, sycl::access::mode::read_write> actors, sycl::accessor<std::array<vecType, 2>, 1, sycl::access::mode::read> walls, sycl::stream out) {
    Actor* currentActor = &actors[currentIndex];

    vecType pos = currentActor->getPos();

    float mi = currentActor->getMass();
    float v0i = 2.0f;
    vecType e0i = normalize(getDirectionVector(currentActor->getPos(), currentActor->getDestination()));
    vecType vi = currentActor->getVelocity();

    vecType personalImpulse = mi * (((v0i * e0i) - vi) / Ti);

    vecType peopleForces = {0, 0};
    for (int x = 0; x < actors.size(); x++) {
        Actor neighbour = actors[x];
        if (currentIndex != x && !neighbour.getAtDestination()) {
            float rij = neighbour.getRadius() + currentActor->getRadius();
            vecType currentToNeighbour = pos - neighbour.getPos();
            float dij = magnitude(currentToNeighbour);
            vecType nij = (currentToNeighbour) / dij;
            vecType tij = getTangentialVector(nij);
            float g = dij > rij ? 0 : rij - dij;
            float deltavtij = dotProduct((neighbour.getVelocity() - currentActor->getVelocity()), tij);

            peopleForces += (Ai * exp((rij - dij) / Bi) + K1 * g) * nij + (K2 * g * deltavtij * tij);
        }
    }

    vecType wallForces = {0, 0};
    for (int x = 0; x < walls.size(); x++) {
        std::array<vecType, 2> currentWall = walls[x];
        float ri = currentActor->getRadius();
        std::pair<float, vecType> dAndn = getDistanceAndNiw(pos, currentWall);
        float diw = dAndn.first;
        float g = diw > ri ? 0 : ri - diw;
        vecType niw = dAndn.second;
        vecType tiw = getTangentialVector(niw);

        wallForces += (Ai * exp((ri - diw) / Bi) + K1 * g) * niw - (K2 * g * dotProduct(vi, tiw) * tiw);
    }

    vecType forceSum = personalImpulse + peopleForces + wallForces;
    vecType acceleration = forceSum / mi;

    //out << "People Forces: (" << peopleForces[0] << ", " << peopleForces[1] << ")    " << z << sycl::endl;
    //out << "Wall Forces: (" << wallForces[0] << ", " << wallForces[1] << ")    " << z << sycl::endl;
    //out << "Acceleration: (" << acceleration[0] << ", " << acceleration[1] << ")    " << z << sycl::endl;
    //out << "-----------------------" << sycl::endl;

    currentActor->setVelocity(vi + acceleration * TIMESTEP);
    currentActor->setPos(pos + currentActor->getVelocity() * TIMESTEP);

    vecType newPos = currentActor->getPos();
    vecType destination = currentActor->getDestination();

    std::array<float, 4> destinationBoundingBox = {destination[0] + 0.01f, destination[0] - 0.01f, destination[1] + 0.01f, destination[1] - 0.01f};
    if (newPos[0] <= destinationBoundingBox[0] && newPos[0] >= destinationBoundingBox[1]
        && pos[1] <= destinationBoundingBox[2] && pos[1] >= destinationBoundingBox[3]) {
            currentActor->setAtDestination(true);
        }
}
