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
        if (!config.HasMember("width")) missingParameters += "width ";
        if (!config.HasMember("height")) missingParameters += "height ";
        if (!config.HasMember("scale")) missingParameters += "scale ";
        if (!config.HasMember("delay")) missingParameters += "delay ";
        if (!config.HasMember("heatmap")) missingParameters += "heatmap ";

        if (!jsonDoc["environment"].HasMember("walls")) missingParameters += "walls ";

        if (jsonDoc["actors"].GetArray().Size() > 0) {
            auto actorParams = {
                "pos", "velocity", "desiredSpeed", "path",
                "pathSize", "mass", "radius"
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

void parseInputFile(std::string filename, std::vector<Actor> &actors, Room &room) {
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
    int width = config["width"].GetInt();
    int height = config["height"].GetInt();
    int scale = config["scale"].GetInt();
    int delay = config["delay"].GetInt();
    bool heatmap = config["heatmap"].GetBool();

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

        actors.push_back(Actor(pos, velocity, desiredSpeed, path, pathSize, mass, radius, atDestination, color));
    }

    // std::cout << "Config: " << std::endl;
    // std::cout << "width: " << width << ", height: " << height << ", scale: " << scale << ", delay: " << delay << ", heatmap: " << heatmap << std::endl << std::endl;

    // std::cout << "Environment:" << std::endl;
    // for (auto w : walls) {
    //     std::cout << "{{" << w[0][0] << ", " << w[0][1] << "}, {" << w[1][0] << ", " << w[1][1] << "}}" << std::endl;
    // }

    // std::cout << std::endl << "Actors:" << std::endl;
    // for (auto a : actors) {
    //     std::cout << "pos: {" << a.getPos()[0] << ", " << a.getPos()[1] << "}, velocity: {" << a.getVelocity()[0] << ", " << a.getVelocity()[1] << "}, desiredSpeed: " << a.getDesiredSpeed() << ", path: ";
    //     for (auto p : a.getPath()) {
    //         std::cout << "{" << p[0] << ", " << p[1] << "}, ";
    //     }
    //     std::cout << std::endl << ", mass: " << a.getMass() << ", radius: " << a.getRadius() << ", atDestination: " << a.getAtDestination() << ", color: [" << a.getColor()[0] << ", " << a.getColor()[1] << ", " << a.getColor()[2] << "]" << std::endl;
    // }
}   
