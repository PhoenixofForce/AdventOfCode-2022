#include "Day12.h"

int main() {
    std::vector<std::string> input{};
    getLines(input, 2022, 12);

    int startX;
    int startY;

    bool foundStart = false;
    for(int x = 0; x < input.size(); x++) {
        const std::string s{ input.at(x) };
        for(int y = 0; y < s.size(); y++) {
            if(s.at(y) == 'S') {
                startX = x;
                startY = y;

                foundStart = true;
                break;
            }
        }
        if(foundStart) break;
    }

    State startingStart{startX, startY, 'S', 0};
    State out = paths::a_star<State>(startingStart, 
            [&input](std::vector<State>& out, const State& current){ addStates(out, input, current); },
            isEnd,
            State::hash
        );

    print() << out.x  << " " << out.y << " = " << out.height << " in " << std::abs(out.moves) << " moves";

    int shortestStartMoves = out.moves;
    for(int x = 0; x < input.size(); x++) {
        const std::string s{ input.at(x) };
        for(int y = 0; y < s.size(); y++) {
            if(s.at(y) == 'a') {
                State start{x, y, 'a', 0};
                int path = paths::a_star<State>(start, 
                    [&input](std::vector<State>& out, const State& current){ addStates(out, input, current); },
                    isEnd,
                    State::hash,
                    false
                ).moves;

                if(path > shortestStartMoves && path != 0) shortestStartMoves = path;
            }
        }
    }
    print() << std::abs(shortestStartMoves);

    return 0;
}

bool isEnd(const State& state) {
    return state.height == 'E';
}

void addStates(std::vector<State>& list, const std::vector<std::string>& map, const State& current) {
    //std::cout << current.x << " " << current.y << " " << current.height << std::endl;

    if(current.x > 0) {
        int newX = current.x - 1;
        int newY = current.y;

        char newHeight = map.at(newX).at(newY);

        if(getHeight(current.height) + 1 >= getHeight(newHeight)) {
            list.push_back({ newX, newY, newHeight, current.moves - 1 });
        }
    }

    if(current.x < map.size() - 1) {
        int newX = current.x + 1;
        int newY = current.y;

        char newHeight = map.at(newX).at(newY);

        if(getHeight(current.height) + 1 >= getHeight(newHeight)) {
            list.push_back({ newX, newY, newHeight, current.moves - 1 });
        }
    }

    if(current.y > 0) {
        int newX = current.x;
        int newY = current.y - 1;

        char newHeight = map.at(newX).at(newY);

        if(getHeight(current.height) + 1 >= getHeight(newHeight)) {
            list.push_back({ newX, newY, newHeight, current.moves - 1 });
        }
    }

    if(current.y < map.at(0).size() - 1) {
        int newX = current.x;
        int newY = current.y + 1;

        char newHeight = map.at(newX).at(newY);

        if(getHeight(current.height) + 1 >= getHeight(newHeight)) {
            list.push_back({ newX, newY, newHeight, current.moves - 1 });
        }
    }
}

int getHeight(char c) {
    if(c == 'S') return getHeight('a');
    if(c == 'E') return getHeight('z');

    return c - 'a';
}