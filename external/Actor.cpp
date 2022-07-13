#include "Actor.hpp"

Actor::Actor(vecType pPos, vecType pVelocity, float pDesiredSpeed, int pPathId,
             float pMass, float pRadius, bool pAtDestination,
             std::array<int, 3> pColor, bool pHeatmapEnabled)
    : pos(pPos), velocity(pVelocity), desiredSpeed(pDesiredSpeed),
      pathId(pPathId), mass(pMass), radius(pRadius),
      atDestination(pAtDestination), color(pColor),
      heatmapEnabled(pHeatmapEnabled), variation({0, 0}), destinationIndex(0),
      bBox({0, 0}) {}

SYCL_EXTERNAL vecType Actor::getPos() const { return pos; }

SYCL_EXTERNAL vecType Actor::getVelocity() const { return velocity; }

SYCL_EXTERNAL float Actor::getDesiredSpeed() const { return desiredSpeed; }

SYCL_EXTERNAL int Actor::getPathId() const { return pathId; }

SYCL_EXTERNAL int Actor::getDestinationIndex() const {
    return destinationIndex;
}

SYCL_EXTERNAL vecType Actor::getVariation() const { return variation; }

SYCL_EXTERNAL float Actor::getMass() const { return mass; }

SYCL_EXTERNAL float Actor::getRadius() const { return radius; }

SYCL_EXTERNAL bool Actor::getAtDestination() const { return atDestination; }

SYCL_EXTERNAL std::array<int, 3> Actor::getColor() const { return color; }

SYCL_EXTERNAL bool Actor::getHeatmapEnabled() const { return heatmapEnabled; }

SYCL_EXTERNAL std::array<int, 2> Actor::getBBox() const { return bBox; }

SYCL_EXTERNAL uint Actor::getSeed() const { return seed; }

SYCL_EXTERNAL void Actor::setPos(vecType newPos) { pos = newPos; }

SYCL_EXTERNAL void Actor::setVelocity(vecType newVelocity) {
    velocity = newVelocity;
}

SYCL_EXTERNAL void Actor::setDesiredSpeed(float newDesiredSpeed) {
    desiredSpeed = newDesiredSpeed;
}

SYCL_EXTERNAL void Actor::setVariation(vecType newVariation) {
    variation = newVariation;
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

SYCL_EXTERNAL void Actor::refreshVariations() {
    // Previous RNG output is used as next seed
    seed = randXorShift(seed);
    float xDirection = float(seed) > 2151000064 ? -1.0f : 1.0f;
    seed = randXorShift(seed);
    float yDirection = float(seed) > 2151000064 ? -1.0f : 1.0f;

    seed = randXorShift(seed);
    float randX = float(seed) * (1.0f / 4294967296.0f) * xDirection;
    seed = randXorShift(seed);
    float randY = float(seed) * (1.0f / 4294967296.0f) * yDirection;
    this->setVariation({randX, randY});
}

SYCL_EXTERNAL void Actor::checkAtDestination(std::array<vecType, 4> destination,
                                             int pathSize) {
    // Destinations are defined as rectangular regions
    if (pos[0] >= destination[0][0] && pos[0] <= destination[2][0] &&
        pos[1] >= destination[0][1] && pos[1] <= destination[2][1]) {
        if (destinationIndex >= PATHALLOCATIONSIZE - 1 ||
            destinationIndex >= pathSize - 1) {
            this->setAtDestination(true);
        } else {
            destinationIndex++;
        }
    }
}
