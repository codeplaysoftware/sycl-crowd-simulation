#ifndef CreateEnv_hpp
#define CreateEnv_hpp

#include <iostream>
#include <array>
#include <vector>
#include <sycl/sycl.hpp>
#include "Room.hpp"
#include "Actor.hpp"
#include "VectorMaths.hpp"

enum class RoomConfgurations {fourSquare, evacuateRoom};

void createEnv(Room &room, std::vector<Actor> &actors, RoomConfgurations type);

#endif
