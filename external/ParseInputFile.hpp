/***************************************************************************
 *
 *  Copyright (C) 2022 Codeplay Software Ltd.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  Codeplay's crowd-simulation
 *
 *  ParseInputFile.hpp
 *
 *  Description:
 *    Parse input JSON file and load configuration into simulation
 *
 **************************************************************************/

#ifndef ParseInputFile_hpp
#define ParseInputFile_hpp

#include "Actor.hpp"
#include "Path.hpp"
#include "Room.hpp"
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
                    Room &room, std::vector<Path> &paths, int &width,
                    int &height, int &scale, int &delay,
                    std::array<int, 3> &bgColor, std::array<int, 3> &wallColor,
                    bool &heatmapEnabled);

#endif
