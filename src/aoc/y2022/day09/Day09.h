#ifndef DAY09_H
#define DAY09_H

#include "../Utils.h"
#include "../util/strings.h"
#include "../util/stream.h"
#include "../util/a_star.h"

#include <iostream>
#include <string>
#include <algorithm>

struct Pos {
    int x{};
    int y {};

    int distanceX(const Pos& rhs) const {
        return std::abs(rhs.x - x);
    }

    int distanceY(const Pos& rhs) const {
        return std::abs(rhs.y - y);
    }

    bool operator==(const Pos& rhs) const { 
        return x == rhs.x && y == rhs.y; 
    }
};

#endif