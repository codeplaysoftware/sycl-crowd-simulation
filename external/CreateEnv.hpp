#ifndef CreateEnv_hpp
#define CreateEnv_hpp

#include <iostream>
#include <array>
#include <vector>
#include <sycl/sycl.hpp>
#include "Room.hpp"
#include "Actor.hpp"

enum class RoomConfgurations {fourSquare};

void createEnv(Room &room, std::vector<Actor> &actors, RoomConfgurations type);

#endif
