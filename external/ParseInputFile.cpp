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
 *  ParseInputFile.cpp
 *
 *  Description:
 *    Parse input JSON file and load configuration into simulation
 *
 **************************************************************************/

#include "ParseInputFile.hpp"

// Checks that input json file contains required members
void validateParameters(rapidjson::Document &jsonDoc) {
    std::string missingParameters = "";

    if (!jsonDoc.HasMember("config"))
        missingParameters += "config ";
    if (!jsonDoc.HasMember("room"))
        missingParameters += "room ";
    if (!jsonDoc.HasMember("actors"))
        missingParameters += "actors ";
    if (!jsonDoc.HasMember("paths"))
        missingParameters += "paths ";

    if (missingParameters != "") {
        throw JSONException("Missing these parameters: " + missingParameters);
    } else {
        auto &config = jsonDoc["config"];
        auto configParams = {"width",     "height",  "scale",         "delay",
                             "wallColor", "bgColor", "heatmapEnabled"};
        for (auto p : configParams) {
            if (!config.HasMember(p))
                missingParameters += std::string(p) + " ";
        }

        if (!jsonDoc["room"].HasMember("walls"))
            missingParameters += "walls ";

        auto actorParams = {"pos",  "velocity", "desiredSpeed",  "pathId",
                            "mass", "radius",   "atDestination", "color"};
        for (auto &a : jsonDoc["actors"].GetArray()) {
            for (auto p : actorParams) {
                if (!a.HasMember(p))
                    missingParameters += std::string(p) + " ";
            }
        }

        for (auto &p : jsonDoc["paths"].GetArray()) {
            if (!p.HasMember("id"))
                missingParameters += "id ";
            if (!p.HasMember("checkpoints"))
                missingParameters += "checkpoints ";
        }

        if (missingParameters != "") {
            throw JSONException("Missing these parameters: " +
                                missingParameters);
        }
    }
}

void parseInputFile(std::string filename, std::vector<Actor> &actors,
                    Room &room, std::vector<Path> &paths, int &WIDTH,
                    int &HEIGHT, int &SCALE, int &DELAY,
                    std::array<int, 3> &BGCOLOR, std::array<int, 3> &WALLCOLOR,
                    bool &HEATMAPENABLED) {
    std::ifstream jsonFile(filename);
    if (!jsonFile.is_open()) {
        throw JSONException("Error opening file " + filename);
    }

    std::stringstream jsonContents;
    jsonContents << jsonFile.rdbuf();

    rapidjson::Document jsonDoc;
    jsonDoc.Parse(jsonContents.str().c_str());

    validateParameters(jsonDoc);

    // Config
    auto &config = jsonDoc["config"];
    WIDTH = config["width"].GetInt();
    HEIGHT = config["height"].GetInt();
    SCALE = config["scale"].GetInt();
    DELAY = config["delay"].GetInt();
    WALLCOLOR = {config["wallColor"][0].GetInt(),
                 config["wallColor"][1].GetInt(),
                 config["wallColor"][2].GetInt()};
    BGCOLOR = {config["bgColor"][0].GetInt(), config["bgColor"][1].GetInt(),
               config["bgColor"][2].GetInt()};
    HEATMAPENABLED = config["heatmapEnabled"].GetBool();

    // Room
    auto jsonWalls = jsonDoc["room"]["walls"].GetArray();
    std::vector<std::array<sycl::float2, 2>> walls;
    for (auto &w : jsonWalls) {
        walls.push_back({sycl::float2({w[0].GetFloat(), w[1].GetFloat()}),
                         sycl::float2({w[2].GetFloat(), w[3].GetFloat()})});
    }
    room.setWalls(walls);

    // Paths
    auto jsonPaths = jsonDoc["paths"].GetArray();
    for (auto &p : jsonPaths) {
        int id = p["id"].GetInt();
        auto jsonCheckpoints = p["checkpoints"].GetArray();
        std::array<std::array<sycl::float2, 2>, PATHALLOCATIONSIZE> checkpoints;
        if (jsonCheckpoints.Size() > PATHALLOCATIONSIZE) {
            throw JSONException(
                "Path Size exceeds amount allocated in memory\nEither reduce "
                "path size or increase PATHALLOCATIONSIZE in 'Path.hpp'");
        }
        for (int i = 0; i < jsonCheckpoints.Size(); i++) {
            std::array<sycl::float2, 2> region;
            region[0] = sycl::float2({jsonCheckpoints[i][0][0].GetFloat(),
                                      jsonCheckpoints[i][0][1].GetFloat()});
            region[1] = sycl::float2({jsonCheckpoints[i][1][0].GetFloat(),
                                      jsonCheckpoints[i][1][1].GetFloat()});
            checkpoints[i] = region;
        }
        int pathSize = jsonCheckpoints.Size();
        paths.push_back(Path(id, checkpoints, pathSize));
    }

    // Actor
    auto jsonActors = jsonDoc["actors"].GetArray();
    for (auto &a : jsonActors) {
        sycl::float2 pos = {a["pos"][0].GetFloat(), a["pos"][1].GetFloat()};
        sycl::float2 velocity = {a["velocity"][0].GetFloat(),
                                 a["velocity"][1].GetFloat()};
        float desiredSpeed = a["desiredSpeed"].GetFloat();
        int pathId = a["pathId"].GetInt();
        int pathSize = paths[pathId].getPathSize();
        int mass = a["mass"].GetInt();
        float radius = a["radius"].GetFloat();
        bool atDestination = a["atDestination"].GetBool();

        auto jsonColor = a["color"].GetArray();
        std::array<int, 3> color = {jsonColor[0].GetInt(),
                                    jsonColor[1].GetInt(),
                                    jsonColor[2].GetInt()};

        actors.push_back(Actor(pos, velocity, desiredSpeed, pathId, mass,
                               radius, atDestination, color));
    }
}
