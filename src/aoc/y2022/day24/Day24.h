#ifndef DAY24_H
#define DAY24_H

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
    char dir{};

    int distance(const Pos& other) const {
        return std::abs(other.x - x) + std::abs(other.y - y);
    } 

    bool operator==(const Pos& rhs) const { 
        return x == rhs.x &&  y == rhs.y;
    }
    
    bool operator<(const Pos& rhs) const { 
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }

    static size_t hash(const Pos& pos) {
        size_t out = 17;
        out *= 31 + pos.x;
        out *= 31 * pos.y;
        return out;
    } 
};

struct State { 
    Pos currentPos{};
    std::vector<Pos> blizzards{};
    int moves = 0;
    
    Pos end{};
    int blizzardCycle;

    bool operator==(const State& rhs) const { 
        return ((-moves) % blizzardCycle == (-rhs.moves) % blizzardCycle) && currentPos == rhs.currentPos;
    }
    
    bool operator<(const State& rhs) const { 
        return moves < rhs.moves;
    }

    static size_t hash(const State& pos) {
        size_t out = 17;
        out *= 31 + Pos::hash(pos.currentPos);
        out *= 31 + ((-pos.moves) % pos.blizzardCycle);
        return out;
    } 
};

void generateStates(std::vector<State>& out, const State& current, int width, int height, const Pos& start, const Pos& end);

#endif