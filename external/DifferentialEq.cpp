#include <iostream>
#include <vector>
#include <array>
#include <sycl.hpp>
#include "DifferentialEq.hpp"
#include "Actor.hpp"
#include "Room.hpp"
#include "MathHelper.hpp"

SYCL_EXTERNAL void differentialEq(int z, sycl::accessor<Actor, 1, sycl::access::mode::read_write> actors, sycl::accessor<std::array<vecType, 2>, 1, sycl::access::mode::read> walls, sycl::stream out) {
    Actor* i = &actors[z];

    auto pos = i->getPos();
     
    auto mi = i->getMass();
    auto v0i = 2;
    auto e0i = normalize(getDirectionVector(i->getPos(), i->getDestination()));
    auto vi = i->getVelocity();

    auto personalImpulse = mi * (((v0i * e0i) - vi) / Ti);

    vecType peopleForces = {0, 0};
    for (int x = 0; x < actors.size(); x++) {
        auto j = actors[x];
        if (z != x && !j.getAtDestination()) {
            auto rij = j.getRadius() + i->getRadius();
            auto dij = magnitude(i->getPos() - j.getPos());
            auto nij = (i->getPos() - j.getPos()) / dij;
            vecType tij = {-nij[1], nij[0]};
            auto g = dij > rij ? 0 : rij - dij;
            auto deltavtij = dotProduct((j.getVelocity() - i->getVelocity()), tij);

            peopleForces += (Ai * exp((rij - dij) / Bi) + K1 * g) * nij + (K2 * g * deltavtij * tij);
        }
    }

    vecType wallForces = {0, 0};
    for (int x = 0; x < walls.size(); x++) {
        auto w = walls[x];
        auto ri = i->getRadius();
        auto diw = distanceToWall(pos, w);
        auto g = diw > ri ? 0 : ri - diw;
        auto niw = getniw(pos, w);
        vecType tiw = {-niw[1], niw[0]};

        wallForces += (Ai * exp((ri - diw) / Bi) + K1 * g) * niw - (K2 * g * dotProduct(vi, tiw) * tiw);
    }

    vecType forceSum = personalImpulse + peopleForces + wallForces;
    auto acceleration = forceSum / mi;

    //out << "People Forces: (" << peopleForces[0] << ", " << peopleForces[1] << ")    " << z << sycl::endl;
    //out << "Wall Forces: (" << wallForces[0] << ", " << wallForces[1] << ")    " << z << sycl::endl;
    //out << "Acceleration: (" << acceleration[0] << ", " << acceleration[1] << ")    " << z << sycl::endl;
    //out << "-----------------------" << sycl::endl;

    i->setVelocity(i->getVelocity() + forceSum * 0.001);
    i->setPos(i->getPos() + i->getVelocity() * 0.001);

    if (i->getPos()[0] <= i->getDestination()[0] + 0.01 && i->getPos()[0] >= i->getDestination()[0] - 0.01
        && i->getPos()[1] <= i->getDestination()[1] + 0.01 && i->getPos()[1] >= i->getDestination()[1] - 0.01) {
            i->setAtDestination(true);
        }
}
