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
        auto configParams = {"width", "height",    "scale",
                             "delay", "wallColor", "bgColor"};
        for (auto p : configParams) {
            if (!config.HasMember(p))
                missingParameters += std::string(p) + " ";
        }

        if (!jsonDoc["room"].HasMember("walls"))
            missingParameters += "walls ";

        auto actorParams = {"pos",           "velocity", "desiredSpeed",
                            "pathId",        "mass",     "radius",
                            "atDestination", "color",    "heatmapEnabled"};
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
                    std::array<int, 3> &BGCOLOR,
                    std::array<int, 3> &WALLCOLOR) {
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
    for (int x; x < 3; x++) {
        BGCOLOR[x] = config["bgColor"][x].GetFloat();
        WALLCOLOR[x] = config["wallColor"][x].GetFloat();
    }

    // Room
    auto jsonWalls = jsonDoc["room"]["walls"].GetArray();
    std::vector<std::array<vecType, 2>> walls;
    for (auto &w : jsonWalls) {
        walls.push_back({vecType({w[0].GetFloat(), w[1].GetFloat()}),
                         vecType({w[2].GetFloat(), w[3].GetFloat()})});
    }
    room.setWalls(walls);

    // Paths
    auto jsonPaths = jsonDoc["paths"].GetArray();
    for (auto &p : jsonPaths) {
        int id = p["id"].GetInt();
        auto jsonCheckpoints = p["checkpoints"].GetArray();
        std::array<std::array<vecType, 2>, PATHALLOCATIONSIZE> checkpoints;
        if (jsonCheckpoints.Size() > PATHALLOCATIONSIZE) {
            throw JSONException(
                "Path Size exceeds amount allocated in memory\nEither reduce "
                "path size or increase PATHALLOCATIONSIZE in 'Path.hpp'");
        }
        for (int i = 0; i < jsonCheckpoints.Size(); i++) {
            std::array<vecType, 2> region;
            region[0] = vecType({jsonCheckpoints[i][0][0].GetFloat(),
                                 jsonCheckpoints[i][0][1].GetFloat()});
            region[1] = vecType({jsonCheckpoints[i][1][0].GetFloat(),
                                 jsonCheckpoints[i][1][1].GetFloat()});
            checkpoints[i] = region;
        }
        int pathSize = jsonCheckpoints.Size();
        paths.push_back(Path(id, checkpoints, pathSize));
    }

    // Actor
    auto jsonActors = jsonDoc["actors"].GetArray();
    for (auto &a : jsonActors) {
        vecType pos = {a["pos"][0].GetFloat(), a["pos"][1].GetFloat()};
        vecType velocity = {a["velocity"][0].GetFloat(),
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

        bool heatmapEnabled = a["heatmapEnabled"].GetBool();

        actors.push_back(Actor(pos, velocity, desiredSpeed, pathId, mass,
                               radius, atDestination, color, heatmapEnabled));
    }
}
