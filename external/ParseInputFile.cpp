#include "ParseInputFile.hpp"

void validateParameters(rapidjson::Document& jsonDoc) {
    std::string missingParameters = "";

    if (!jsonDoc.HasMember("config")) missingParameters += "config ";
    if (!jsonDoc.HasMember("environment")) missingParameters += "environment ";
    if (!jsonDoc.HasMember("actors")) missingParameters += "actors ";
    
    if (missingParameters != "") {
        throw JSONException("Missing these parameters: " + missingParameters);
    }
    else {
        auto& config = jsonDoc["config"];
        auto configParams = {
            "width", "height", "scale", "delay"
        };
        for (auto p : configParams) {
            if (!config.HasMember(p)) missingParameters += std::string(p) + " ";
        }

        if (!jsonDoc["environment"].HasMember("walls")) missingParameters += "walls ";

        if (jsonDoc["actors"].GetArray().Size() > 0) {
            auto actorParams = {
                "pos", "velocity", "desiredSpeed", "path",
                "pathSize", "mass", "radius", "heatmapEnabled"
            };
            for (auto& a : jsonDoc["actors"].GetArray()) { 
                for (auto p : actorParams) {
                    if (!a.HasMember(p)) missingParameters += std::string(p) + " ";
                }
            }
        }

        if (missingParameters != "") {
            throw JSONException("Missing these parameters: " + missingParameters);
        }
    }
}

void parseInputFile(std::string filename, std::vector<Actor> &actors, Room &room, int &WIDTH, int &HEIGHT, int &SCALE, int &DELAY) {
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
    auto& config = jsonDoc["config"];
    WIDTH = config["width"].GetInt();
    HEIGHT = config["height"].GetInt();
    SCALE = config["scale"].GetInt();
    DELAY = config["delay"].GetInt();

    // Environment
    auto jsonWalls = jsonDoc["environment"]["walls"].GetArray();
    std::vector<std::array<vecType, 2>> walls;
    for (auto& w : jsonWalls) {
        walls.push_back({vecType({w[0].GetFloat(), w[1].GetFloat()}), vecType({w[2].GetFloat(), w[3].GetFloat()})});
    }
    room.setWalls(walls);

    // Actor
    auto jsonActors = jsonDoc["actors"].GetArray();
    for (auto& a : jsonActors) {
        vecType pos = {a["pos"][0].GetFloat(), a["pos"][1].GetFloat()};
        vecType velocity = {a["velocity"][0].GetFloat(), a["velocity"][1].GetFloat()};
        float desiredSpeed = a["desiredSpeed"].GetFloat();
        
        auto jsonPath = a["path"].GetArray();
        std::array<vecType, PATHALLOCATIONSIZE> path;
        for (int x = 0; x < jsonPath.Size(); x++) {
            path[x] = {jsonPath[x][0].GetFloat(), jsonPath[x][1].GetFloat()};
        }

        int pathSize = a["pathSize"].GetInt();
        int mass = a["mass"].GetInt();
        float radius = a["radius"].GetFloat();
        bool atDestination = a["atDestination"].GetBool();
        
        auto jsonColor = a["color"].GetArray();
        std::array<int, 3> color = {jsonColor[0].GetInt(), jsonColor[1].GetInt(), jsonColor[2].GetInt()};

        bool heatmapEnabled = a["heatmapEnabled"].GetBool();

        actors.push_back(Actor(pos, velocity, desiredSpeed, path, pathSize, mass, radius, atDestination, color, heatmapEnabled));
    }
}   
