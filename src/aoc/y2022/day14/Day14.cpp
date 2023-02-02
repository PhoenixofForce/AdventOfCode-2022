#include "Day14.h"

int main() {
    std::vector<std::string> input{};
    getLines(input, 2022, 14);

    std::set<Pos> map{};
    int maxY = 0;

    for(const std::string& line: input) {
        std::vector<std::string> splitString{};
        strings::split(splitString, line, " -> ");
        
        for(int i = 0; i < splitString.size() - 1; i++) {
            Pos from{ stringToPos(splitString.at(i)) };
            Pos to{ stringToPos(splitString.at(i + 1)) };
            int currentMaxY = fillMap(map, from, to, ROCK);
            if(currentMaxY > maxY) maxY = currentMaxY;
        }
    }

    fillMap(map, {-10000, maxY + 2}, {10000, maxY + 2}, ROCK);

    Pos sandSpawner{500, 0};
    int sandRested{};
    
    bool firstPart = false;
    while(map.find({500, 0}) == map.end()) {
        Pos sand{ sandSpawner.x, sandSpawner.y };
        bool change = true;
        
        while(change) {
            if(map.find({ sand.x, sand.y + 1 }) == map.end()) {
                sand.y += 1;
            } else if(map.find({ sand.x - 1, sand.y + 1 }) == map.end()) {
                sand.x -= 1;
                sand.y += 1;
            } else if(map.find({ sand.x + 1, sand.y + 1 }) == map.end()) {
                sand.x += 1;
                sand.y += 1;
            } else {
                change = false;
                map.insert(sand);
                sandRested++;
            }
        }

        if(sand.y >= maxY && !firstPart) {
            print() << sandRested - 1; //minus one, because for part 2 the one that fell into eternity rested
            firstPart = true;
        }
    }
    print() << sandRested;

    return 0;
}

int fillMap(std::set<Pos>& map, Pos from, Pos to, int e) {
    int maxY = 0;

    int dx = to.x - from.x;
    dx /= std::abs(dx);
    int dy = to.y - from.y;
    dy /= std::abs(dy);

    map.insert(from);
    map.insert(to);

    if(from.x == to.x) {
        for(int y = from.y; y != to.y; y += dy) {
            map.insert({from.x, y});
            if(y > maxY) maxY = y;
        }
    } else if(from.y == to.y) {
        for(int x = from.x; x != to.x; x += dx) {
            map.insert({x, from.y});
        }
        maxY = from.y;
    }

    return std::max(maxY, std::max(from.y, to.y));
}

Pos stringToPos(const std::string& s) {
    std::vector<std::string> splitString{};
    strings::split(splitString, s, ",");
    return { std::stoi(splitString.at(0)), std::stoi(splitString.at(1)) };
}

size_t std::hash<Pos>::operator()(const Pos& state) const { 
    size_t out = 17;
    out = out * 31 + state.x;
    out = out * 31 + state.y;
    return out;
} 