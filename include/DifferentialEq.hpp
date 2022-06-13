#ifndef DifferentialEqu_hpp
#define DifferentialEqu_hpp

#include <iostream>
#include <vector>
#include <array>
#include "Actor.hpp"
#include "Room.hpp"
#include "MathHelper.hpp"

const float Ai = 2000;
const float Bi = 0.08;
const float k1 = 125000;
const float k2 = 240000;
const float ti = 0.5;

void DifferentialEqu(Actor actor);

#endif