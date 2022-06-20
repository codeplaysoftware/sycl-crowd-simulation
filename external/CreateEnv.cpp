#include "CreateEnv.hpp"

void createEnv(Room &room, std::vector<Actor> &actors, RoomConfgurations type) {
    if (type == RoomConfgurations::fourSquare) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                actors.push_back(Actor{{0.5f + (i * 0.5f), 0.5f + (j * 0.5f)},
                        {0.01, 0.01}, 
                        {0.02, 0.02},
                        {6.5f + (i * 0.5f), 6.5f + (j * 0.5f)},
                        50, 0.05, false, {255, 0, 0}});
            }
        }

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                actors.push_back(Actor{{6.5f + (i * 0.5f), 0.5f + (j * 0.5f)},
                        {0.01, 0.01}, 
                        {0.02, 0.02},
                        {0.5f + (i * 0.5f), 6.5f + (j * 0.5f)},
                        50, 0.05, false, {0, 255, 0}});
            }
        }

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                actors.push_back(Actor{{6.5f + (i * 0.5f), 6.5f + (j * 0.5f)},
                        {0.01, 0.01}, 
                        {0.02, 0.02},
                        {0.5f + (i * 0.5f), 0.5f + (j * 0.5f)},
                        50, 0.05, false, {0, 0, 255}});
            }
        }

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                actors.push_back(Actor{{0.5f + (i * 0.5f), 6.5f + (j * 0.5f)},
                        {0.01, 0.01}, 
                        {0.02, 0.02},
                        {6.5f + (i * 0.5f), 0.5f + (j * 0.5f)},
                        50, 0.05, false, {150, 150, 150}});
            }
        }

        room.setWalls({{vecType{3.15, 3.15}, vecType{4.25, 3.15}}, 
                      {vecType{4.25, 3.15}, vecType{4.25, 4.25}}, 
                      {vecType{4.25, 4.25}, vecType{3.15, 4.25}},
                      {vecType{3.15, 4.25}, vecType{3.15, 3.15}}, 

                      {vecType{4.75, 3.15}, vecType{5.85, 3.15}},
                      {vecType{5.85, 3.15}, vecType{5.85, 4.25}},
                      {vecType{5.85, 4.25}, vecType{4.75, 4.25}},
                      {vecType{4.75, 4.25}, vecType{4.75, 3.15}},

                      {vecType{3.15, 4.75}, vecType{4.25, 4.75}},
                      {vecType{4.25, 4.75}, vecType{4.25, 5.85}},
                      {vecType{4.25, 5.85}, vecType{3.15, 5.85}},
                      {vecType{3.15, 5.85}, vecType{3.15, 4.75}},

                      {vecType{4.75, 4.75}, vecType{5.85, 4.75}},
                      {vecType{5.85, 4.75}, vecType{5.85, 5.85}},
                      {vecType{5.85, 5.85}, vecType{4.75, 5.85}},
                      {vecType{4.75, 5.85}, vecType{4.75, 4.75}},
        });
    }
}
