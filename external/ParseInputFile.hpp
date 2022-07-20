#ifndef ParseInputFile_hpp
#define ParseInputFile_hpp

#include "Actor.hpp"
#include "Path.hpp"
#include "Room.hpp"
#include "VectorMaths.hpp"
#include <array>
#include <fstream>
#include <iostream>
#include <rapidjson/document.h>
#include <sstream>
#include <string>
#include <sycl/sycl.hpp>
#include <vector>

class JSONException : public std::runtime_error {
  public:
    JSONException(const std::string errorMessage)
        : std::runtime_error(errorMessage) {}
};

void validateParameters(rapidjson::Document &jsonDoc);

void parseInputFile(std::string filename, std::vector<Actor> &actors,
                    Room &room, std::vector<Path> &paths, int &WIDTH,
                    int &HEIGHT, int &SCALE, int &DELAY, std::array<int, 3> &BGCOLOR, std::array<int, 3> &WALLCOLOR);

#endif
