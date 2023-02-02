#ifndef DAY15_H
#define DAY15_H

#include "../Utils.h"
#include "../util/strings.h"
#include "../util/stream.h"
#include "../util/a_star.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_set>

struct Pos { 
    int x{}; 
    int y{}; 

    int distance(const Pos& other) const {
        return std::abs(other.x - x) + std::abs(other.y - y);
    } 

    bool operator==(const Pos& rhs) const { 
        return x == rhs.x &&  y == rhs.y;
    }
    
    bool operator<(const Pos& rhs) const { 
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
};

template <>
class std::hash<Pos> {
 public:
  size_t operator()(const Pos& state) const;
};
struct Sensor {
    Pos sensorPos;
    Pos closestBeacons;
};

Sensor stringToSensor(const std::string& line);

#endif