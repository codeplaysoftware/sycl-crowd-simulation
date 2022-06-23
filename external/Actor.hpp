#ifndef Actor_hpp
#define Actor_hpp

#include <iostream>
#include <array>
#include <random>
#include <vector>
#include <sycl/sycl.hpp>
#include "VectorMaths.hpp"

const int PATHALLOCATIONSIZE = 10;

class Actor {
private:
    vecType pos;
    vecType velocity;
    float desiredSpeed;
    std::array<vecType, PATHALLOCATIONSIZE> path;
    int pathSize;
    int destinationIndex;
    vecType variation;
    float mass;
    float radius;
    bool atDestination;
    std::array<int, 3> color;
    bool heatmapEnabled;

public:    
    Actor(vecType pPos, vecType pVelocity, float pdesiredSpeed, std::array<vecType, PATHALLOCATIONSIZE> pPath, int pathSize, float pMass, float pRadius, bool pAtDestination, std::array<int, 3> pColor, bool pHeatmapEnabled);
    
    SYCL_EXTERNAL vecType getPos() const;
    SYCL_EXTERNAL vecType getVelocity() const;
    SYCL_EXTERNAL float getDesiredSpeed() const;
    SYCL_EXTERNAL std::array<vecType, PATHALLOCATIONSIZE> getPath() const;
    SYCL_EXTERNAL vecType getDestination() const;
    SYCL_EXTERNAL vecType getVariation() const;
    SYCL_EXTERNAL float getMass() const;
    SYCL_EXTERNAL float getRadius() const;
    SYCL_EXTERNAL bool getAtDestination() const;
    SYCL_EXTERNAL std::array<int, 3> getColor() const;
    SYCL_EXTERNAL bool getHeatmapEnabled() const;

    SYCL_EXTERNAL void setPos(vecType newPos);
    SYCL_EXTERNAL void setVelocity(vecType newVelocity);
    SYCL_EXTERNAL void setDesiredSpeed(float newDesiredSpeed);
    SYCL_EXTERNAL void setPath(std::array<vecType, PATHALLOCATIONSIZE> newPath);
    SYCL_EXTERNAL void setVariation(vecType newVariation);
    SYCL_EXTERNAL void setAtDestination(bool param);
    SYCL_EXTERNAL void setColor(std::array<int, 3> newColor);

    SYCL_EXTERNAL void checkAtDestination();
    void refreshVariation();
};

#endif
