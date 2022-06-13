#ifndef Room_hpp
#define Room_hpp

#include <iostream>
#include <vector>
#include <array>

class Room {
private:
    std::vector<std::array<float, 4>> walls;
public:    
    Room(std::vector<std::array<float, 4>> pWalls);

    std::vector<std::array<float, 4>> getWalls();
};

#endif