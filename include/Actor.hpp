#ifndef Actor_hpp
#define Actor_hpp

#include <iostream>
#include <array>
#include <sycl/sycl.hpp>
#include "GeometricVector.hpp"

class Actor {
private:
    GeometricVector pos;
    GeometricVector velocity;
    GeometricVector desiredVelocity;
    GeometricVector destination;
    float mass;
    float radius;
public:    
    Actor(GeometricVector pPos, GeometricVector pVelocity, GeometricVector pDesiredVelocity, GeometricVector pDestination, float pMass, float pRadius);
    
    SYCL_EXTERNAL GeometricVector getPos();
    SYCL_EXTERNAL GeometricVector getVelocity();
    SYCL_EXTERNAL GeometricVector getDesiredVelocity();
    SYCL_EXTERNAL GeometricVector getDestination();
    SYCL_EXTERNAL float getMass();
    SYCL_EXTERNAL float getRadius();

    SYCL_EXTERNAL void setPos(GeometricVector newPos);
    SYCL_EXTERNAL void setVelocity(GeometricVector newVelocity);
    SYCL_EXTERNAL void setDesiredVelocity(GeometricVector newDesiredVelocity);
    SYCL_EXTERNAL void setDestination(GeometricVector newDestination);
};

#endif
