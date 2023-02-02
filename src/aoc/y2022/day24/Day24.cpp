#include "Day24.h"


int main() {
    std::vector<std::string> input{};
    getLines(input, 2022, 24);

    int height = input.size() - 1;
    int width = input.at(0).size() - 1;

    std::vector<Pos> blizzards{};   

    Pos start{};
    Pos end{};
    for(int y = 0; y < input.size(); y++) {
        for(int x = 0;  x < input.at(y).size(); x++) {
            char c = input.at(y).at(x);
            
            if(c == '.') {
                if(y == 0) start = {x, y};
                if(y == height) end = {x, y};
            }
            else if(c == '#');
            else blizzards.push_back({x, y, c});
        }
    }
    std::cout << "find path from " << start.x << " | " << start.y << " to " << end.x << " | " << end.y << std::endl;

    int moves = 0;
    
    std::cout << "start seach, " << width << ", " << height << std::endl;
    State endState = paths::a_star<State>(
        State{ start, blizzards, 0, end, (height - 1) * (width - 1)},
        [&](std::vector<State>& out, const State& current ){ generateStates(out, current, width, height, start, end); },
        [&end](const State& current){ return current.currentPos == end; },
        State::hash,
        true, true,
        [](const State current){ return "current moves " + std::to_string(-current.moves) + " at " + std::to_string(current.currentPos.x) + " | " + std::to_string(current.currentPos.y); }
    );

    print() << std::abs(endState.moves) << std::endl;

    //back to start
    endState = paths::a_star<State>(
        endState,
        [&](std::vector<State>& out, const State& current ){ generateStates(out, current, width, height, start, end); },
        [&start](const State& current){ return current.currentPos == start; },
        State::hash,
        true, true,
        [](const State current){ return "current moves " + std::to_string(-current.moves) + " at " + std::to_string(current.currentPos.x) + " | " + std::to_string(current.currentPos.y); }
    );

    //back to end
    endState = paths::a_star<State>(
        endState,
        [&](std::vector<State>& out, const State& current ){ generateStates(out, current, width, height, start, end); },
        [&end](const State& current){ return current.currentPos == end; },
        State::hash,
        true, true,
        [](const State current){ return "current moves " + std::to_string(-current.moves) + " at " + std::to_string(current.currentPos.x) + " | " + std::to_string(current.currentPos.y); }
    );

    print() << std::abs(endState.moves) << std::endl;

    return 0;
}

void generateStates(std::vector<State>& out, const State& current, int width, int height, const Pos& start, const Pos& end) {
    static std::map<int, std::vector<Pos>> blizzardCache{};

    State stateCopy = current;
    stateCopy.moves--;

    if(blizzardCache.find(stateCopy.moves) != blizzardCache.end()) {
        stateCopy.blizzards = blizzardCache[stateCopy.moves];
    } else {
        for(Pos& blizz: stateCopy.blizzards) {
            Pos dir{};
            if(blizz.dir == '^') dir = { 0, -1};
            if(blizz.dir == '>') dir = { 1,  0};
            if(blizz.dir == 'v') dir = { 0,  1};
            if(blizz.dir == '<') dir = {-1,  0};

            blizz.x += dir.x;
            blizz.y += dir.y;

            if(blizz.x == 0) blizz.x = width - 1;
            if(blizz.x == width) blizz.x = 1;
            if(blizz.y == 0) blizz.y = height - 1;
            if(blizz.y == height) blizz.y = 1;
        }
        blizzardCache[stateCopy.moves] = stateCopy.blizzards;
    }

    Pos up   { stateCopy.currentPos.x, stateCopy.currentPos.y - 1 };
    Pos down { stateCopy.currentPos.x, stateCopy.currentPos.y + 1 };
    Pos left { stateCopy.currentPos.x - 1, stateCopy.currentPos.y };
    Pos right{ stateCopy.currentPos.x + 1, stateCopy.currentPos.y };

    bool shouldPrint = stateCopy.currentPos.x == 1 && stateCopy.currentPos.y == 2;

    auto isWall = [&](const Pos& pos){
        if(pos == start || pos == end) return false;
        return pos.x <= 0 || pos.x >= width || pos.y <= 0 || pos.y >= height;
    };

    if(!isWall(up)) {
        if(std::find(stateCopy.blizzards.begin(), stateCopy.blizzards.end(), up) == stateCopy.blizzards.end()) {
            State stateOut = stateCopy;
            stateOut.currentPos = up;
            out.push_back(stateOut);
        }
    }

    if(!isWall(down)) {
        if(std::find(stateCopy.blizzards.begin(), stateCopy.blizzards.end(), down) == stateCopy.blizzards.end()) {
            State stateOut = stateCopy;
            stateOut.currentPos = down;
            out.push_back(stateOut);
        }
    }

    if(!isWall(left)) {
        if(std::find(stateCopy.blizzards.begin(), stateCopy.blizzards.end(), left) == stateCopy.blizzards.end()) {
            State stateOut = stateCopy;
            stateOut.currentPos = left;
            out.push_back(stateOut);
        }
    }

    if(!isWall(right)) {
        if(std::find(stateCopy.blizzards.begin(), stateCopy.blizzards.end(), right) == stateCopy.blizzards.end()) {
            State stateOut = stateCopy;
            stateOut.currentPos = right;
            out.push_back(stateOut);
        }
    }

    if(std::find(stateCopy.blizzards.begin(), stateCopy.blizzards.end(), stateCopy.currentPos) == stateCopy.blizzards.end()) {
        State stateOut = stateCopy;
        out.push_back(stateOut);
    }
}