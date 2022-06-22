#ifndef ParseInputFile_hpp
#define ParseInputFile_hpp

#include <iostream>
#include <array>
#include <vector>
#include <sstream>
#include <fstream>
#include <sycl/sycl.hpp>
#include <rapidjson/document.h>
#include "VectorMaths.hpp"
#include "Actor.hpp"
#include "Room.hpp"

void parseInputFile(std::string filename, std::vector<Actor> &actors, Room &room);

#endif
