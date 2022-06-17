#include "DifferentialEq.hpp"

SYCL_EXTERNAL void differentialEq(int z, sycl::accessor<Actor, 1, sycl::access::mode::read_write> actors, sycl::accessor<std::array<vecType, 2>, 1, sycl::access::mode::read> walls, sycl::stream out) {
    Actor* i = &actors[z];

    vecType pos = i->getPos();

    float mi = i->getMass();
    float v0i = 2.0f;
    vecType e0i = normalize(getDirectionVector(i->getPos(), i->getDestination()));
    vecType vi = i->getVelocity();

    vecType personalImpulse = mi * (((v0i * e0i) - vi) / Ti);

    vecType peopleForces = {0, 0};
    for (int x = 0; x < actors.size(); x++) {
        Actor j = actors[x];
        if (z != x && !j.getAtDestination()) {
            float rij = j.getRadius() + i->getRadius();
            float dij = magnitude(pos - j.getPos());
            vecType nij = (pos - j.getPos()) / dij;
            vecType tij = {-nij[1], nij[0]};
            float g = dij > rij ? 0 : rij - dij;
            float deltavtij = dotProduct((j.getVelocity() - i->getVelocity()), tij);

            peopleForces += (Ai * exp((rij - dij) / Bi) + K1 * g) * nij + (K2 * g * deltavtij * tij);
        }
    }

    vecType wallForces = {0, 0};
    for (int x = 0; x < walls.size(); x++) {
        std::array<vecType, 2> w = walls[x];
        float ri = i->getRadius();
        std::pair<float, vecType> dAndn = getDistanceAndNiw(pos, w);
        float diw = dAndn.first;
        float g = diw > ri ? 0 : ri - diw;
        vecType niw = dAndn.second;
        vecType tiw = {-niw[1], niw[0]};

        wallForces += (Ai * exp((ri - diw) / Bi) + K1 * g) * niw - (K2 * g * dotProduct(vi, tiw) * tiw);
    }

    vecType forceSum = personalImpulse + peopleForces + wallForces;
    vecType acceleration = forceSum / mi;

    //out << "People Forces: (" << peopleForces[0] << ", " << peopleForces[1] << ")    " << z << sycl::endl;
    //out << "Wall Forces: (" << wallForces[0] << ", " << wallForces[1] << ")    " << z << sycl::endl;
    //out << "Acceleration: (" << acceleration[0] << ", " << acceleration[1] << ")    " << z << sycl::endl;
    //out << "-----------------------" << sycl::endl;

    i->setVelocity(vi + forceSum * 0.001);
    i->setPos(pos + i->getVelocity() * 0.001);

    vecType newPos = i->getPos();
    vecType destination = i->getDestination();

    if (newPos[0] <= destination[0] + 0.01 && newPos[0] >= destination[0] - 0.01
        && pos[1] <= destination[1] + 0.01 && pos[1] >= destination[1] - 0.01) {
            i->setAtDestination(true);
        }
}
