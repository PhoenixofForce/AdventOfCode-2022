#ifndef DAY22_H
#define DAY22_H

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
};

void parseInput(std::vector<std::string>& out, const std::string& in);

#endif