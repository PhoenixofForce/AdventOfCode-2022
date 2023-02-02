#include "Day23.h"

int main() {
    std::vector<std::string> input{};
    getLines(input, 2022, 23);

    std::vector<Elf> elfes{};
    for(int y = 0; y < input.size(); y++) {
        for(int x = 0; x < input.at(y).size(); x++) {
            if(input.at(y).at(x) == '#') elfes.push_back({x, y});
        }
    }

    std::vector<char> directions = {'N', 'S', 'W', 'E'};
    std::vector<int> directionsDX = {0, 0, -1, 1};
    std::vector<int> directionsDY = {-1, 1, 0, 0};

    int rounds = 0;
    bool elfMoved = true;
    while(elfMoved) {
        std::cout << "started round " << rounds << ", with direction " << directions.at(0) << " = (" << directionsDX.at(0) << " | " << directionsDY.at(0) << ")" << std::endl;
        elfMoved = false;

        //propose moves
        for(Elf& e: elfes) {
            e.standsStill = true;
            if(countSuroundingElfes(elfes, e) == 0) {
                continue;
            }

            for(int d = 0; d < directions.size(); d++) {
                int elfesInDirection = countElfesInDirection(elfes, e, directions.at(d));
                if(elfesInDirection == 0) {
                    e.wantX = e.x + directionsDX.at(d);
                    e.wantY = e.y + directionsDY.at(d);
                    e.standsStill = false;
                    break;
                }
            }
        }

        //make moves
        for(Elf& e: elfes) {
            if(e.standsStill) continue;

            bool otherElfSamePosition = std::find_if(elfes.begin(), elfes.end(), [&e](const Elf& other){
                if(e.x == other.x && e.y == other.y) return false;          //not the same elf
                if(other.standsStill) return false;                         //other not standing still
                return other.wantX == e.wantX && other.wantY == e.wantY;    // the same want position
            }) != elfes.end();

            if(!otherElfSamePosition) {
                e.x = e.wantX;
                e.y = e.wantY;
                elfMoved = true;
            }
        }

        //cycle direction
        directions.push_back(directions.at(0));
        directions.erase(directions.begin());
        directionsDX.push_back(directionsDX.at(0));
        directionsDX.erase(directionsDX.begin());
        directionsDY.push_back(directionsDY.at(0));
        directionsDY.erase(directionsDY.begin());
        rounds++;

        if(rounds == 10) {   //print part 1
            int minX = 100000, maxX = -100000, minY = 100000, maxY = -100000;
            for(const Elf& e: elfes) {
                if(e.x > maxX) maxX = e.x;
                if(e.x < minX) minX = e.x;
                if(e.y > maxY) maxY = e.y;
                if(e.y < minY) minY = e.y;
            }

            int out = (maxX - minX + 1) * (maxY - minY + 1) - elfes.size();
            print() << out << std::endl;
        }
    }
    print() << rounds << std::endl;

    return 0;
}

int countSuroundingElfes(const std::vector<Elf>& elfes, Elf& current) {
    current.NE = 0;
    current.NW = 0;
    current.NS = 0;
    current.NN = 0;

    int out = 0;
    for(int dx = -1; dx <= 1; dx++) {
        for(int dy = -1; dy <= 1; dy++) {
            if(dx == 0 && dy == 0) continue;
            if(std::find(elfes.begin(), elfes.end(), Elf{current.x + dx, current.y + dy}) != elfes.end()) {
                out++;
                if(dx == -1) current.NW++;
                if(dy == -1) current.NN++;
                if(dx == 1) current.NE++;
                if(dy == 1) current.NS++;
            }
        }
    }
    return out;
}

int countElfesInDirection(const std::vector<Elf>& elfes, const Elf& current, char direction) {
    if(direction == 'N') {
        int out = current.NN;
        return out;
    }

    if(direction == 'S') {
        int out = current.NS;
        return out;
    }

    if(direction == 'W') {
        int out = current.NW;
        return out;
    }

    if(direction == 'E') {
        int out = current.NE;
        return out;
    }

    return 0;
}