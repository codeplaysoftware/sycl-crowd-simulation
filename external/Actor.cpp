#include "Actor.hpp"

Actor::Actor(vecType pPos, vecType pVelocity, float pDesiredSpeed, int pPathId,
             float pMass, float pRadius, bool pAtDestination,
             std::array<int, 3> pColor, bool pHeatmapEnabled)
    : pos(pPos), velocity(pVelocity), desiredSpeed(pDesiredSpeed),
      pathId(pPathId), mass(pMass), radius(pRadius),
      atDestination(pAtDestination), color(pColor),
      heatmapEnabled(pHeatmapEnabled), destinationIndex(0), bBox({0, 0}) {}

SYCL_EXTERNAL vecType Actor::getPos() const { return pos; }

SYCL_EXTERNAL vecType Actor::getVelocity() const { return velocity; }

SYCL_EXTERNAL float Actor::getDesiredSpeed() const { return desiredSpeed; }

SYCL_EXTERNAL int Actor::getPathId() const { return pathId; }

SYCL_EXTERNAL int Actor::getDestinationIndex() const {
    return destinationIndex;
}

SYCL_EXTERNAL float Actor::getMass() const { return mass; }

SYCL_EXTERNAL float Actor::getRadius() const { return radius; }

SYCL_EXTERNAL bool Actor::getAtDestination() const { return atDestination; }

SYCL_EXTERNAL std::array<int, 3> Actor::getColor() const { return color; }

SYCL_EXTERNAL bool Actor::getHeatmapEnabled() const { return heatmapEnabled; }

SYCL_EXTERNAL std::array<int, 2> Actor::getBBox() const { return bBox; }

SYCL_EXTERNAL uint Actor::getSeed() const { return seed; }

SYCL_EXTERNAL float Actor::getForce() const { return force; }

SYCL_EXTERNAL void Actor::setPos(vecType newPos) { pos = newPos; }

SYCL_EXTERNAL void Actor::setVelocity(vecType newVelocity) {
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

SYCL_EXTERNAL void Actor::checkAtDestination(std::array<vecType, 2> destination,
                                             int pathSize) {
    // Destinations are defined as rectangular regions
    if (pos[0] >= destination[0][0] && pos[0] <= destination[1][0] &&
        pos[1] >= destination[0][1] && pos[1] <= destination[1][1]) {
        if (destinationIndex >= PATHALLOCATIONSIZE - 1 ||
            destinationIndex >= pathSize - 1) {
            this->setAtDestination(true);
        } else {
            destinationIndex++;
        }
    }
}