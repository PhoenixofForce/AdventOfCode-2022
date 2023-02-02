#include "Day09.h"

int main() {
    bool part2 = true;
    std::vector<std::string> input{};
    getLines(input, 2022, 9);

    std::map<std::string, Pos> directions{};
    directions["R"] = {1, 0}; 
    directions["L"] = {-1, 0}; 
    directions["U"] = {0, 1}; 
    directions["D"] = {0, -1}; 

    int ropeLength = part2? 10: 2;
    std::vector<Pos> rope{};
    for(int i = 0; i < ropeLength; i++) rope.push_back({0, 0});
    
    std::vector<Pos> tailPositions{};
    tailPositions.push_back(rope.at(ropeLength - 1));

    for(const std::string& line: input) {
        std::vector<std::string> splitLine{};
        strings::split(splitLine, line, " ");

        Pos direction{ directions[splitLine.at(0)] };
        int steps = std::stoi(splitLine.at(1));
        
        std::cout << line << std::endl;
        for(int i = 0; i < steps; i++) {
            rope.at(0).x += direction.x;
            rope.at(0).y += direction.y;

            for(int ropeIndex = 1; ropeIndex < ropeLength; ropeIndex++) {
                const Pos& previosKnot{ rope.at(ropeIndex - 1) };
                Pos& currentKnot{ rope.at(ropeIndex) };

                int dx = previosKnot.x - currentKnot.x;
                dx /= std::abs(dx);
                int dy = previosKnot.y - currentKnot.y;
                dy /= std::abs(dy);

                if(previosKnot.distanceX(currentKnot) == 2 && previosKnot.distanceY(currentKnot) == 0) {
                    currentKnot.x += dx;
                } else if(previosKnot.distanceX(currentKnot) == 0 && previosKnot.distanceY(currentKnot) == 2) {
                    currentKnot.y += dy;
                } else if(previosKnot.distanceX(currentKnot) + previosKnot.distanceY(currentKnot) >= 3) {
                    currentKnot.x += dx;
                    currentKnot.y += dy;
                }
            }

            tailPositions.push_back(rope.at(ropeLength - 1));
        }

    }

    print(part2) << Stream<Pos>::of(tailPositions).distinct().size();

    return 0;
}