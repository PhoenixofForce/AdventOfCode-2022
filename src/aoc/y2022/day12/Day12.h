#ifndef DAY12_H
#define DAY12_H

#include "../Utils.h"
#include "../util/strings.h"
#include "../util/stream.h"
#include "../util/a_star.h"

#include <iostream>
#include <string>
#include <algorithm>

#include "../util/a_star.h"

struct State {
    int x{};
    int y{};
    char height{};
    int moves{};

    static size_t hash(const State& state) {
      size_t out = 17;
      out = out * 31 + state.x;
      out = out * 31 + state.y;
      return out;
    }
};

bool operator<(const State& lhs, const State& rhs) {
    return lhs.moves < rhs.moves;
}

bool operator==(const State& lhs, const State& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool isEnd(const State& state);
void addStates(std::vector<State>& list, const std::vector<std::string>& map, const State& current);

int getHeight(char c);

#endif