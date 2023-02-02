#include "Day18.h"

int main() {
    std::vector<Pos> input{};
    getLines(input, 2022, 18, Pos::fromString);

    int out = 0;
    for(const Pos& cube: input) {
        if(!contains(input, Pos{cube.x-1, cube.y, cube.z})) out++;
        if(!contains(input, Pos{cube.x+1, cube.y, cube.z})) out++;
        if(!contains(input, Pos{cube.x, cube.y-1, cube.z})) out++;
        if(!contains(input, Pos{cube.x, cube.y+1, cube.z})) out++;
        if(!contains(input, Pos{cube.x, cube.y, cube.z-1})) out++;
        if(!contains(input, Pos{cube.x, cube.y, cube.z+1})) out++;
    }
    print() << out << std::endl;

    int maxX = Stream<Pos>::of(input).map<int>([](const Pos& p){ return p.x; }).max().value_or(0);
    int maxY = Stream<Pos>::of(input).map<int>([](const Pos& p){ return p.y; }).max().value_or(0);
    int maxZ = Stream<Pos>::of(input).map<int>([](const Pos& p){ return p.z; }).max().value_or(0);

    Pos maxPos{maxX, maxY, maxZ};
    std::vector<Pos> outsideAir{};
    floodFillAir(outsideAir, input, Pos{0, 0, 0}, maxPos);

    out = 0;
    for(const Pos& cube: input) {
        if(!contains(input, Pos{cube.x-1, cube.y, cube.z}) && contains(outsideAir, Pos{cube.x-1, cube.y, cube.z})) out++;
        if(!contains(input, Pos{cube.x+1, cube.y, cube.z}) && contains(outsideAir, Pos{cube.x+1, cube.y, cube.z})) out++;
        if(!contains(input, Pos{cube.x, cube.y-1, cube.z}) && contains(outsideAir, Pos{cube.x, cube.y-1, cube.z})) out++;
        if(!contains(input, Pos{cube.x, cube.y+1, cube.z}) && contains(outsideAir, Pos{cube.x, cube.y+1, cube.z})) out++;
        if(!contains(input, Pos{cube.x, cube.y, cube.z-1}) && contains(outsideAir, Pos{cube.x, cube.y, cube.z-1})) out++;
        if(!contains(input, Pos{cube.x, cube.y, cube.z+1}) && contains(outsideAir, Pos{cube.x, cube.y, cube.z+1})) out++;
    }
    print() << out;

    return 0;
}

void floodFillAir(std::vector<Pos>& out, const std::vector<Pos>& input, const Pos& start, const Pos& max) {
    out.push_back(start);

    for(int i = 0; i < out.size(); i++) {
        Pos cubeCurrent{ out.at(i) };

        if(cubeCurrent.x >= max.x+2 || cubeCurrent.y >= max.y+2 || cubeCurrent.z >= max.z+2 ||
            cubeCurrent.x <= -2 || cubeCurrent.y <= -2 || cubeCurrent.z <= -2) continue;

        Pos next = Pos{ cubeCurrent.x-1, cubeCurrent.y, cubeCurrent.z};
        if(!contains(input, next) && !contains(out, next)) out.push_back(next);

        next = Pos{ cubeCurrent.x+1, cubeCurrent.y, cubeCurrent.z};
        if(!contains(input, next) && !contains(out, next)) out.push_back(next);

        next = Pos{ cubeCurrent.x, cubeCurrent.y-1, cubeCurrent.z};
        if(!contains(input, next) && !contains(out, next)) out.push_back(next);

        next = Pos{ cubeCurrent.x, cubeCurrent.y+1, cubeCurrent.z};
        if(!contains(input, next) && !contains(out, next)) out.push_back(next);

        next = Pos{ cubeCurrent.x, cubeCurrent.y, cubeCurrent.z-1};
        if(!contains(input, next) && !contains(out, next)) out.push_back(next);

        next = Pos{ cubeCurrent.x, cubeCurrent.y, cubeCurrent.z+1};
        if(!contains(input, next) && !contains(out, next)) out.push_back(next);
    }
}

bool contains(const std::vector<Pos>& l, const Pos& p) {
    return std::find(l.begin(), l.end(), p) != l.end();
}