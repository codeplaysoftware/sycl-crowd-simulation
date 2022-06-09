#ifndef Room_hpp
#define Room_hpp

#include<iostream>
#include <vector>
#include <array>

class Room {
private:
    std::vector<std::array<float, 4>> walls;
    std::vector<std::array<float, 2>> destinations;
public:    
    Room(std::vector<std::array<float, 4>> pWalls, std::vector<std::array<float, 2>> pDestinations);

    std::vector<std::array<float, 4>> getWalls();
    std::vector<std::array<float, 2>> getDestinations();
};

#endif