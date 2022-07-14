#ifndef ParseInputFile_hpp
#define ParseInputFile_hpp

#include <iostream>
#include <array>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <sycl/sycl.hpp>
#include <rapidjson/document.h>
#include "VectorMaths.hpp"
#include "Actor.hpp"
#include "Room.hpp"
#include "Path.hpp"

class JSONException : public std::runtime_error {
public:
    JSONException(const std::string errorMessage) : std::runtime_error(errorMessage) {}
};

void validateParameters(rapidjson::Document& jsonDoc);

void parseInputFile(std::string filename, std::vector<Actor> &actors, Room &room, std::vector<Path> &paths, int &WIDTH, int &HEIGHT, int &SCALE, int &DELAY);

#endif
