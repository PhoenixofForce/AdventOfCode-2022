#include "Day08.h"

int main() {
    std::vector<std::string> input{};
    getLines(input, 2022, 8);

    int out = 0;
    int highestScenicScore = 0;

    for(int x = 0; x < input.size(); x++) {
        for(int y = 0; y < input.size(); y++) {
            if(isLeftEdgeVisible(input, x, y) ||
                isRightEdgeVisible(input, x, y) ||
                isTopEdgeVisible(input, x, y) ||
                isBottomEdgeVisible(input, x, y)) out++;

            int scenicScore = getLeftVisibleCount(input, x, y) *
                                getRightVisibleCount(input, x, y) *
                                getTopVisibleCount(input, x, y) *
                                getBottomVisibleCount(input, x, y);

            if(highestScenicScore < scenicScore) highestScenicScore = scenicScore;
        }
    }
    print() << out;
    print() << highestScenicScore;

    return 0;
}

bool isLeftEdgeVisible(const std::vector<std::string> map, int x, int y) {
    int treeHeight = getValue(map, x, y);
    for(int i = x - 1; i >= 0; i--) {
        if(getValue(map, i, y) >= treeHeight) return false;
    }

    return true;
}

bool isRightEdgeVisible(const std::vector<std::string> map, int x, int y) {
    int treeHeight = getValue(map, x, y);
    for(int i = x + 1; i < map.size(); i++) {
        if(getValue(map, i, y) >= treeHeight) return false;
    }

    return true;
}

bool isTopEdgeVisible(const std::vector<std::string> map, int x, int y) {
    int treeHeight = getValue(map, x, y);
    for(int i = y - 1; i >= 0; i--) {
        if(getValue(map, x, i) >= treeHeight) return false;
    }

    return true;
}

bool isBottomEdgeVisible(const std::vector<std::string> map, int x, int y) {
    int treeHeight = getValue(map, x, y);
    for(int i = y + 1; i < map.at(x).size(); i++) {
        if(getValue(map, x, i) >= treeHeight) return false;
    }

    return true;
}

// PART 2

int getLeftVisibleCount(const std::vector<std::string> map, int x, int y) {
    int treeHeight = getValue(map, x, y);
    int out = 0;

    for(int i = x - 1; i >= 0; i--) {
        out++;
        if(getValue(map, i, y) >= treeHeight) return out;
    }

    return out;
}
int getRightVisibleCount(const std::vector<std::string> map, int x, int y) {
    int treeHeight = getValue(map, x, y);
    int out = 0;

    for(int i = x + 1; i < map.size(); i++) {
        out++;
        if(getValue(map, i, y) >= treeHeight) return out;
    }

    return out;
}
int getTopVisibleCount(const std::vector<std::string> map, int x, int y) {
    int treeHeight = getValue(map, x, y);
    int out = 0;

    for(int i = y - 1; i >= 0; i--) {
        out++;
        if(getValue(map, x, i) >= treeHeight) return out;
    }

    return out;
}
int getBottomVisibleCount(const std::vector<std::string> map, int x, int y) {
    int treeHeight = getValue(map, x, y);
    int out = 0;

    for(int i = y + 1; i < map.at(x).size(); i++) {
        out++;
        if(getValue(map, x, i) >= treeHeight) return out;
    }

    return out;
}

int getValue(const std::vector<std::string> map, int x, int y) {
    std::string out{ map.at(x).at(y) };
    return std::stoi(out);
}