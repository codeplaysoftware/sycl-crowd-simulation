#include <iostream>
#include <vector>
#include <array>
#include <sycl.hpp>
#include "DifferentialEq.hpp"
#include "Actor.hpp"
#include "Room.hpp"
#include "MathHelper.hpp"

SYCL_EXTERNAL void differentialEq(Actor &i, sycl::accessor<Actor, 1> actors, sycl::accessor<std::array<float, 4>> walls) {
    auto mi = i.getMass();
    auto v0i = 1.5;
    auto e0i = getDirectionVector(i.getPos(), i.getDestination());
    auto vi = i.getVelocity();

    auto personalImpulse = ((v0i * e0i) - vi) / ti;

    auto peopleForces = getZeroFromVector(e0i);
    for (int x = 0; x < actors.size(); x++) {
        auto j = actors[x];
        if (&j != &i) {
            auto rij = j.getRadius() + i.getRadius();
            auto dij = magnitude(i.getPos() - j.getPos());
            auto nij = (i.getPos() - j.getPos()) / dij;
            auto tij = nij;
            tij = {-nij[1], nij[0]};
            auto g = dij > rij ? 0 : rij - dij;
            auto deltavtij = dotProduct((j.getVelocity() - i.getVelocity()), tij);

            peopleForces += (Ai * exp((rij - dij) / Bi) + k1 * g) * nij + (k2 * g * deltavtij * tij);
        }
    }

    auto wallForces = getZeroFromVector(e0i);
    for (int x = 0; x < walls.size(); x++) {
        auto w = walls[x];
        auto ri = i.getRadius();
        auto diw = distanceToWall(i.getPos(), w);
        auto g = diw > ri ? 0 : ri - diw;
        //auto niw = () / diw
    }
}
