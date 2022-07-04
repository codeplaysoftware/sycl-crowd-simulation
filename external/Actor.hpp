#ifndef Actor_hpp
#define Actor_hpp

#include "Path.hpp"
#include "VectorMaths.hpp"
#include <array>
#include <iostream>
#include <random>
#include <sycl/sycl.hpp>
#include <vector>

class Actor {
  private:
    vecType pos;
    vecType velocity;
    float desiredSpeed;
    int pathId;
    int destinationIndex;
    vecType variation;
    float mass;
    float radius;
    bool atDestination;
    std::array<int, 3> color;
    bool heatmapEnabled;
    std::array<int, 2> bBox;

  public:
    Actor(vecType pPos, vecType pVelocity, float pdesiredSpeed, int pPathId,
          float pMass, float pRadius, bool pAtDestination,
          std::array<int, 3> pColor, bool pHeatmapEnabled);

    SYCL_EXTERNAL vecType getPos() const;
    SYCL_EXTERNAL vecType getVelocity() const;
    SYCL_EXTERNAL float getDesiredSpeed() const;
    SYCL_EXTERNAL int getPathId() const;
    SYCL_EXTERNAL int getDestinationIndex() const;
    SYCL_EXTERNAL vecType getVariation() const;
    SYCL_EXTERNAL float getMass() const;
    SYCL_EXTERNAL float getRadius() const;
    SYCL_EXTERNAL bool getAtDestination() const;
    SYCL_EXTERNAL std::array<int, 3> getColor() const;
    SYCL_EXTERNAL bool getHeatmapEnabled() const;
    SYCL_EXTERNAL std::array<int, 2> getBBox() const;

    SYCL_EXTERNAL void setPos(vecType newPos);
    SYCL_EXTERNAL void setVelocity(vecType newVelocity);
    SYCL_EXTERNAL void setDesiredSpeed(float newDesiredSpeed);
    SYCL_EXTERNAL void setVariation(vecType newVariation);
    SYCL_EXTERNAL void setAtDestination(bool param);
    SYCL_EXTERNAL void setColor(std::array<int, 3> newColor);
    SYCL_EXTERNAL void setBBox(std::array<int, 2> newBBox);

    SYCL_EXTERNAL void checkAtDestination(std::array<vecType, 4> destination,
                                          int pathSize);
};

#endif
