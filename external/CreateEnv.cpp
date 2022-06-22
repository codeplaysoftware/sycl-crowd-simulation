#include "CreateEnv.hpp"

void createEnv(Room &room, std::vector<Actor> &actors, RoomConfgurations type) {
    if (type == RoomConfgurations::fourSquare) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                actors.push_back(Actor{{0.5f + (i * 0.5f), 0.5f + (j * 0.5f)},
                        {0.01, 0.01}, 
                        2.0f,
                        {{6.5f + (i * 0.5f), 6.5f + (j * 0.5f)}},
                        1,
                        50, 0.05, false, {255, 0, 0}});
            }
        }

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                actors.push_back(Actor{{6.5f + (i * 0.5f), 0.5f + (j * 0.5f)},
                        {0.01, 0.01}, 
                        2.0f,
                        {{0.5f + (i * 0.5f), 6.5f + (j * 0.5f)}},
                        1,
                        50, 0.05, false, {0, 255, 0}});
            }
        }

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                actors.push_back(Actor{{6.5f + (i * 0.5f), 6.5f + (j * 0.5f)},
                        {0.01, 0.01}, 
                        2.0f,
                        {{0.5f + (i * 0.5f), 0.5f + (j * 0.5f)}},
                        1,
                        50, 0.05, false, {0, 0, 255}});
            }
        }

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                actors.push_back(Actor{{0.5f + (i * 0.5f), 6.5f + (j * 0.5f)},
                        {0.01, 0.01}, 
                        2.0f,
                        {{6.5f + (i * 0.5f), 0.5f + (j * 0.5f)}},
                        1,
                        50, 0.05, false, {150, 150, 150}});
            }
        }

        room.setWalls({
            {vecType{3.15, 3.15}, vecType{4.25, 3.15}}, 
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

    else if (type == RoomConfgurations::evacuateRoom) {
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 30; j++) {
                actors.push_back(Actor(vecType({4 + (i * 0.2f), 1 + (j * 0.2f)}),
                                    vecType({0.01, 0.01}), 
                                    2.0f, 
                                    {vecType({0.5, 4.1}), vecType({-5, 4.1})}, 
                                    2,
                                    50, 0.05, false, {255, 0, 0}));
            }
        }
        
        room.setWalls({
            {vecType({0.5, 0.5}), vecType({8.5, 0.5})},
            {vecType({8.5, 0.5}), vecType({8.5, 8.5})},
            {vecType({8.5, 8.5}), vecType({0.5, 8.5})},
            {vecType({0.5, 8.5}), vecType({0.5, 4.15})},
            {vecType({0.5, 3.85}), vecType({0.5, 0.5})},
        });
    }

    else if (type == RoomConfgurations::twoExitstwoGroups) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 30; j++) {
                actors.push_back(Actor(vecType({6.5f + (i * 0.2f), 1 + (j * 0.2f)}),
                                    vecType({0.01, 0.01}), 
                                    2.0f, 
                                    {vecType({-1, 4.1})}, 
                                    1,
                                    50, 0.05, false, {255, 0, 0}));
            }
        }
        
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 30; j++) {
                actors.push_back(Actor(vecType({0.8f + (i * 0.2f), 1 + (j * 0.2f)}),
                                    vecType({0.01, 0.01}), 
                                    2.0f, 
                                    {vecType({10, 6.2})}, 
                                    1,
                                    50, 0.05, false, {0, 255, 0}));
            }
        }

        room.setWalls({
            {vecType({0.5, 0.5}), vecType({8.5, 0.5})},
            {vecType({8.5, 0.5}), vecType({8.5, 6})},
            {vecType({8.5, 6.4}), vecType({8.5, 8.5})},
            {vecType({8.5, 8.5}), vecType({0.5, 8.5})},
            {vecType({0.5, 8.5}), vecType({0.5, 4.2})},
            {vecType({0.5, 3.8}), vecType({0.5, 0.5})},
        });
    }
}
