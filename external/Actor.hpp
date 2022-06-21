#ifndef Actor_hpp
#define Actor_hpp

#include <iostream>
#include <array>
#include <random>
#include <sycl/sycl.hpp>
#include "VectorMaths.hpp"

class Actor {
private:
    vecType pos;
    vecType velocity;
    float desiredSpeed;
    vecType destination;
    vecType variation;
    float mass;
    float radius;
    bool atDestination;
    std::array<int, 3> color;

public:    
    Actor(vecType pPos, vecType pVelocity, float pdesiredSpeed, vecType pDestination, float pMass, float pRadius, bool pAtDestination, std::array<int, 3> pColor);
    
    SYCL_EXTERNAL vecType getPos() const;
    SYCL_EXTERNAL vecType getVelocity() const;
    SYCL_EXTERNAL float getDesiredSpeed() const;
    SYCL_EXTERNAL vecType getDestination() const;
    SYCL_EXTERNAL vecType getVariation() const;
    SYCL_EXTERNAL float getMass() const;
    SYCL_EXTERNAL float getRadius() const;
    SYCL_EXTERNAL bool getAtDestination() const;
    SYCL_EXTERNAL std::array<int, 3> getColor() const;

    SYCL_EXTERNAL void setPos(vecType newPos);
    SYCL_EXTERNAL void setVelocity(vecType newVelocity);
    SYCL_EXTERNAL void setDesiredSpeed(float newDesiredSpeed);
    SYCL_EXTERNAL void setDestination(vecType newDestination);
    SYCL_EXTERNAL void setVariation(vecType newVariation);
    SYCL_EXTERNAL void setAtDestination(bool param);
    SYCL_EXTERNAL void setColor(std::array<int, 3> newColor);

    SYCL_EXTERNAL void checkAtDestination();
    void refreshVariation();
};

#endif
