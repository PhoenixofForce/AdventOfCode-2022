#ifndef DAY16_H
#define DAY16_H

#include "../Utils.h"
#include "../util/strings.h"
#include "../util/stream.h"
#include "../util/a_star.h"
#include "../util/combinations.h"

#include <iostream>
#include <string>
#include <algorithm>

//input

struct Point {
    std::string name{};
    int flowRate{};
    std::vector<std::string> followingPoints{};
};

//distances

struct Path {
    std::string current;
    int moves;

    static size_t hash(const Path& state) {
        std::hash<std::string> stringHasher;

        size_t out = 17;
        out = out * 31 + stringHasher(state.current);
        return out;
    }
};

bool operator<(const Path& lhs, const Path& rhs) {
    return lhs.moves < rhs.moves;
}

bool operator==(const Path& lhs, const Path& rhs) {
    return lhs.current == rhs.current;
}

int distance(const std::map<std::string, Point>& stringToPoint, const Point& a, const Point& b);

//part 1

struct State {
    std::string name;
    int totalPressure;
    int minutes;
    std::vector<std::string> openPoints{};

    static size_t hash(const State& state) {
        std::hash<std::string> stringHasher;

        size_t out = 17;
        out = out * 31 + stringHasher(state.name);
        out = out * 31 + state.minutes;
        out = out * 31 + state.totalPressure;
        out *= 31;

        for(const std::string& s: state.openPoints) {
            out += stringHasher(s);
        }

        return out;
    } 
};

bool operator<(const State& lhs, const State& rhs) {
    return lhs.totalPressure < rhs.totalPressure;
}

bool operator==(const State& lhs, const State& rhs) {
    return lhs.name == rhs.name && lhs.totalPressure == rhs.totalPressure && lhs.minutes == rhs.minutes;
}

bool isEnd(std::vector<State>& endOut, const State& end, int MAX_MINUTE);
void generateStates(std::vector<State>& out, const State& current, std::map<std::string, Point>& stringToPoint, std::map<std::tuple<std::string, std::string>, int>& pathLengths, int MAX_MINUTE);

#endif