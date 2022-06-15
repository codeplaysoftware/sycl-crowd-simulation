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
public:    
    Actor(vecType pPos, vecType pVelocity, vecType pDesiredVelocity, vecType pDestination, float pMass, float pRadius);
    
    SYCL_EXTERNAL vecType getPos();
    SYCL_EXTERNAL vecType getVelocity();
    SYCL_EXTERNAL vecType getDesiredVelocity();
    SYCL_EXTERNAL vecType getDestination();
    SYCL_EXTERNAL float getMass();
    SYCL_EXTERNAL float getRadius();

    SYCL_EXTERNAL void setPos(vecType newPos);
    SYCL_EXTERNAL void setVelocity(vecType newVelocity);
    SYCL_EXTERNAL void setDesiredVelocity(vecType newDesiredVelocity);
    SYCL_EXTERNAL void setDestination(vecType newDestination);
};

#endif
