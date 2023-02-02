#ifndef DAY14_H
#define DAY14_H

#include "../Utils.h"
#include "../util/strings.h"
#include "../util/stream.h"
#include "../util/a_star.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <set>

int AIR = 0;
int ROCK = 1;
int SAND = 2;

struct Pos{
    int x{};
    int y{};

    bool operator<(const Pos& rhs) const { 
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
};

template <>
class std::hash<Pos> {
 public:
  size_t operator()(const Pos& state) const;
};

Pos stringToPos(const std::string& s);
int fillMap(std::set<Pos>& map, Pos from, Pos to, int element);

#endif