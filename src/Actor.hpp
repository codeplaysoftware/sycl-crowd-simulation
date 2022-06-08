#ifndef Actor_hpp
#define Actor_hpp

#include<iostream>
#include <array>
using namespace std;

class Actor {
private:
    array<float, 2> pos;
    array<float, 2> velocity;
    array<float, 2> desiredVelocity;
    float mass;
    float radius;
public:    
    Actor(array<float, 2> pPos, array<float, 2> pVelocity, array<float, 2> pDesiredVelocity, float pMass, float pRadius);
};

#endif