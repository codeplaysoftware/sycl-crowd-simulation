#ifndef Actor_hpp
#define Actor_hpp

#include<iostream>
#include <array>

class Actor {
private:
    std::array<float, 2> pos;
    std::array<float, 2> velocity;
    std::array<float, 2> desiredVelocity;
    float mass;
    float radius;
public:    
    Actor(std::array<float, 2> pPos, std::array<float, 2> pVelocity, std::array<float, 2> pDesiredVelocity, float pMass, float pRadius);
    std::array<float, 2> getPos();
    std::array<float, 2> getVelocity();
    std::array<float, 2> getDesiredVelocity();
    float getMass();
    float getRadius();
};

#endif