#ifndef DAY17_H
#define DAY17_H

#include "../Utils.h"
#include "../util/strings.h"
#include "../util/stream.h"
#include "../util/a_star.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <set>

struct Pos { 
    long long x{}; 
    long long y{}; 

    bool operator==(const Pos& rhs) const { 
        return x == rhs.x &&  y == rhs.y;
    }
    
    bool operator<(const Pos& rhs) const { 
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
};

void getRock(std::vector<Pos>& rockOut, int rockType, long long maxY);


#endif