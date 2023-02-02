#include "Day22.h"

int main() {
    bool part2 = true;

    std::vector<std::string> input{};
    getLines(input, 2022, 22);

    int height = input.size() - 2;

    std::string path{ input.at(input.size() - 1) };
    std::vector<std::string> parsedPath{};
    parseInput(parsedPath, path);

    Stream<std::string>::of(parsedPath).print();

    std::vector<int> directionX = {1, 0, -1,  0};
    std::vector<int> directionY = {0, 1,  0,  -1};
    int currentDirection = 0;

    Pos startPos{};
    for(int i = 0; i < input.at(0).size(); i++) {
        if(input.at(0).at(i) == '.') {
            startPos.x = i;
            break;
        }
    }

    int i = -1;
    for(std::string s: parsedPath) {
        i++;

        std::cout << s << ":" << std::endl;

        bool isRock = false;
        if(i % 2 == 1) { // turn
            if(s == "R") currentDirection = (currentDirection + 1) % 4;
            else currentDirection = (4 + currentDirection - 1) % 4;

            std::cout << "  now facing " << currentDirection << std::endl;
        } else { // move
            for(int moves = 0; moves < std::stoi(s); moves++) {
                Pos newPos{startPos.x + directionX.at(currentDirection), startPos.y + directionY.at(currentDirection) };
                int newDirection = currentDirection;

                std::cout << "  "  << startPos.x << " | " << startPos.y << " => " << newPos.x << " | " << newPos.y << std::endl;

                if(!part2) {
                    if(currentDirection == 0) { //right
                        int width = input.at(newPos.y).size();
                        if(newPos.x >= width) newPos.x = 0;
                        while(input.at(newPos.y).at(newPos.x) == ' ') newPos.x++;
                    }
                    if(currentDirection == 1) { //down
                        if(newPos.y >= height || input.at(newPos.y).size() <= newPos.x || input.at(newPos.y).at(newPos.x) == ' ') newPos.y = 0;
                        while(input.at(newPos.y).size() <= newPos.x || input.at(newPos.y).at(newPos.x) == ' ') newPos.y++;
                    }
                    if(currentDirection == 2) { //left
                        int width = input.at(newPos.y).size();

                        if(newPos.x < 0 || input.at(newPos.y).at(newPos.x) == ' ') newPos.x = width - 1;
                        while(input.at(newPos.y).at(newPos.x) == ' ') newPos.x--;
                    }
                    if(currentDirection == 3) { //up
                        if(newPos.y < 0 || input.at(newPos.y).at(newPos.x) == ' ') newPos.y = height - 1;
                        while(input.at(newPos.y).size() <= newPos.x || input.at(newPos.y).at(newPos.x) == ' ') newPos.y--;
                    }
                } else {    //if part2 
                    int newX = newPos.x, newY = newPos.y;
                    if(newPos.x == -1) {
                        if(newPos.y >= 100 && newPos.y < 150) {
                            std::cout << "  case 1" << std::endl;
                            newDirection = 0;
                            newX = 50;
                            newY = 49 - (newPos.y - 100);
                        }

                        else if(newPos.y >= 150 && newPos.y < 200) {
                            std::cout << "  case 2" << std::endl;
                            newDirection = 1;
                            newX = (newPos.y - 150) + 50;
                            newY = 0;
                        }
                    }

                    if(newPos.y == 200) {
                        std::cout << "  case 3" << std::endl;
                        newX += 100;
                        newY = 0;
                    }

                    if(newPos.x == 50 && newPos.y >= 150 && newPos.y < 200 && currentDirection == 0) {
                        std::cout << "  case 4" << std::endl;
                        newDirection = 3;
                        newX = 50 + newPos.y - 150;
                        newY = 149;
                    }

                    if(newPos.y == 150 && newPos.x >= 50 && newPos.x < 100 && currentDirection == 1) {
                        std::cout << "  case 5" << std::endl;
                        newDirection = 2;
                        newY = newPos.x - 50 + 150;
                        newX = 49;
                    }

                    if(newPos.x == 100 && newPos.y >= 100 && newPos.y < 150) {
                        std::cout << "  case 6" << std::endl;
                        newDirection = 2;
                        newX = 149;
                        newY = 49 - (newPos.y - 100);
                    }

                    if(newPos.x == 100 && newPos.y >= 50 && newPos.y < 100 && currentDirection == 0) {
                        std::cout << "  case 7" << std::endl;
                        newDirection = 3;
                        newX = 100 + newPos.y - 50;
                        newY = 49;
                    }

                    if(newPos.y == 50 && newPos.x >= 100 && newPos.x < 150 && currentDirection == 1) {
                        std::cout << "  case 8" << std::endl;
                        newDirection = 2;
                        newY = newPos.x + 50 - 100;
                        newX = 99;
                    }

                    if(newPos.x == 150) {
                        std::cout << "  case 9" << std::endl;
                        newDirection = 2;
                        newX = 99;
                        newY = 149 - newPos.y; 
                         
                    }

                    if(newPos.y == -1) {
                        if(newPos.x >= 100 && newPos.x < 150) {
                            std::cout << "  case 10" << std::endl;
                            newX -= 100;
                            newY = 199;
                        }

                        if(newPos.x >= 50 && newPos.x < 100) {
                            std::cout << "  case 11" << std::endl;
                            newDirection = 0;
                            newY = (newPos.x - 50) + 150;
                            newX = 0;
                        }
                    }

                    if(newPos.x == 49 && newPos.y >= 0 && newPos.y < 50) {
                        std::cout << "  case 12" << std::endl;
                        newDirection = 0;
                        newX = 0;
                        newY = 149 - newPos.y;
                    }

                    if(newPos.x == 49 && newPos.y >= 50 && newPos.y < 100 && currentDirection == 2) {
                        std::cout << "  case 13" << std::endl;
                        newDirection = 1;
                        newX = newPos.y - 50;
                        newY = 100;
                    }

                    if(newPos.y == 99 && newPos.x >= 0 && newPos.x < 50 && currentDirection == 3) {
                        std::cout << "  case 14" << std::endl;
                        newDirection = 0;
                        newX = 50;
                        newY = newPos.x + 50;
                    }

                    if(newPos.x != newX || newPos.y != newY) std::cout << "  jumped to " << newX << " | " << newY << std::endl;

                    newPos.x = newX;
                    newPos.y = newY;
                }

                char tile = input.at(newPos.y).at(newPos.x);
                if(tile == '#') {
                    std::cout << "  found rock at " << newPos.x << " | " << newPos.y << std::endl;
                    isRock = true;
                    break;
                }
                else if(tile == '.') {
                    startPos = newPos;
                    currentDirection = newDirection;
                }
                else std::cout << "  INVALID TILE: '" << tile << "'" << std::endl; 

                std::cout << "  stopped at ( " << startPos.x << " | " << startPos.y << " )" << std::endl;
            }
        }
    }
    std::cout << std::endl << startPos.x << " | " << startPos.y << ", facing " << currentDirection << std::endl;
    print(part2) << (1000 * (startPos.y + 1) + 4 * (startPos.x + 1) + currentDirection) << std::endl;

    return 0;
}

void parseInput(std::vector<std::string>& out, const std::string& in) {
    std::string current = "";
    bool isNumber = true;

    for(int i = 0; i < in.size(); i++) {
        char c = in.at(i);
        bool currentEqualsNumber = c >= '0' && c <= '9';

        if(isNumber != currentEqualsNumber) {
            out.push_back(current);
            current = "";
            isNumber = currentEqualsNumber;
        }

        current += c;
    }
    if(current.size() > 0) out.push_back(current);
}