#ifndef DAY23_H
#define DAY23_H

#include "../Utils.h"
#include "../util/strings.h"
#include "../util/stream.h"
#include "../util/a_star.h"

#include <iostream>
#include <string>
#include <algorithm>

struct Elf {
    int x{};
    int y{};

    int wantX{};
    int wantY{};
    bool standsStill{ false };

    int NN = 0;
    int NE = 0;
    int NW = 0;
    int NS = 0;

    bool operator==(const Elf& rhs) const { 
        return x == rhs.x &&  y == rhs.y;
    }
    
    bool operator<(const Elf& rhs) const { 
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }

};

int countSuroundingElfes(const std::vector<Elf>& elfes, Elf& current);
int countElfesInDirection(const std::vector<Elf>& elfes, const Elf& current, char direction);

#endif