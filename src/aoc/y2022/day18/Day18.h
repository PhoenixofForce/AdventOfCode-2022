#ifndef DAY18_H
#define DAY18_H

#include "../Utils.h"
#include "../util/strings.h"
#include "../util/stream.h"
#include "../util/a_star.h"

#include <iostream>
#include <string>
#include <algorithm>

struct Pos {
    int x{};
    int y{};
    int z{};

    bool operator==(const Pos& rhs) const { 
        return x == rhs.x &&  y == rhs.y && z == rhs.z;
    }
    
    bool operator<(const Pos& rhs) const { 
        return x < rhs.x || (x == rhs.x && y < rhs.y) || (x == rhs.x && y == rhs.y && z < rhs.z);
    }

    static Pos fromString(const std::string& s) {
        Pos out{};
        std::vector<std::string> splitLine{};
        strings::split(splitLine, s, ",");
        
        out.x = std::stoi(splitLine.at(0));
        out.y = std::stoi(splitLine.at(1));
        out.z = std::stoi(splitLine.at(2));

        return out;
    }
};

void floodFillAir(std::vector<Pos>& out, const std::vector<Pos>& input, const Pos& start, const Pos& max);
bool contains(const std::vector<Pos>& l, const Pos& p);

#endif