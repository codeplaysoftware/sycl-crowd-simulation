#ifndef Actor_hpp
#define Actor_hpp

#include <iostream>
#include <array>
#include <sycl/sycl.hpp>

class Actor {
private:
    std::array<float, 2> pos;
    std::array<float, 2> velocity;
    std::array<float, 2> desiredVelocity;
    std::array<float, 2> destination;
    float mass;
    float radius;
public:    
    Actor(std::array<float, 2> pPos, std::array<float, 2> pVelocity, std::array<float, 2> pDesiredVelocity, std::array<float, 2> pDestination, float pMass, float pRadius);
    
    SYCL_EXTERNAL std::array<float, 2> getPos();
    SYCL_EXTERNAL std::array<float, 2> getVelocity();
    SYCL_EXTERNAL std::array<float, 2> getDesiredVelocity();
    SYCL_EXTERNAL std::array<float, 2> getDestination();
    SYCL_EXTERNAL float getMass();
    SYCL_EXTERNAL float getRadius();

    SYCL_EXTERNAL void setPos(std::array<float, 2> newPos);
    SYCL_EXTERNAL void setVelocity(std::array<float, 2> newVelocity);
    SYCL_EXTERNAL void setDesiredVelocity(std::array<float, 2> newDesiredVelocity);
    SYCL_EXTERNAL void setDestination(std::array<float, 2> newDestination);
};

#endif
