#ifndef Actor_hpp
#define Actor_hpp

#include <iostream>
#include <array>
#include <sycl/sycl.hpp>
#include "VectorMaths.hpp"

using vecType = std::array<float, 2>;

class Actor {
private:
    vecType pos;
    vecType velocity;
    vecType desiredVelocity;
    vecType destination;
    float mass;
    float radius;
    bool atDestination;
    std::array<int, 3> color;

public:    
    Actor(vecType pPos, vecType pVelocity, vecType pDesiredVelocity, vecType pDestination, float pMass, float pRadius, bool pAtDestination, std::array<int, 3> pColor);
    
    SYCL_EXTERNAL vecType getPos();
    SYCL_EXTERNAL vecType getVelocity();
    SYCL_EXTERNAL vecType getDesiredVelocity();
    SYCL_EXTERNAL vecType getDestination();
    SYCL_EXTERNAL float getMass();
    SYCL_EXTERNAL float getRadius();
    SYCL_EXTERNAL bool getAtDestination();
    SYCL_EXTERNAL std::array<int, 3> getColor();

    SYCL_EXTERNAL void setPos(vecType newPos);
    SYCL_EXTERNAL void setVelocity(vecType newVelocity);
    SYCL_EXTERNAL void setDesiredVelocity(vecType newDesiredVelocity);
    SYCL_EXTERNAL void setDestination(vecType newDestination);
    SYCL_EXTERNAL void setAtDestination(bool param);
};

#endif
