#include "Day17.h"

int main() {
    std::string input{ getFile(2022, 17) };
    input = strings::trim(input);

    long long leftWallAt = 0;
    long long rightWallAt = 8;
    std::vector<Pos> walls{};
    for(long long x = -20; x <= 20; x++) walls.push_back({x, 0});

    int rockType = 0;
    int streamIndex = 0;

    long long maxY = 0;

    long long maxPieces = 1000000000000;
    for(long long i = 0; i < maxPieces; i++) {
        if(i == 2022) {
            print() << maxY << std::endl << std::endl;
        }

        std::vector<Pos> fallingRock{};
        getRock(fallingRock, rockType, maxY);
        
        if(i % 1000 == 0 || (i >= 999999998829 && i % 100 == 0)) std::cout << "rock " << i << " spawned at y= " << fallingRock.at(0).y <<  ", current max " << maxY << std::endl; 

        bool isFalling = true;
        while(isFalling) {
            //push
            char pushDirection = input.at(streamIndex);
            long long directionX = pushDirection == '>'? 1: -1;

            bool cancelPush = false;
            for(const Pos& piece: fallingRock) {
                if(piece.x + directionX == leftWallAt || piece.x + directionX == rightWallAt || std::find(walls.begin(), walls.end(), Pos{piece.x + directionX, piece.y}) != walls.end()) {
                    cancelPush = true;
                    break;
                }
            }

            if(!cancelPush) {
                for(Pos& piece: fallingRock) {
                    piece.x += directionX;
                }
            }

            //fall
            bool cancelFall = false;
            for(const Pos& piece: fallingRock) {
                if(std::find(walls.begin(), walls.end(), Pos{piece.x, piece.y - 1}) != walls.end() || piece.y == 0) {
                    cancelFall = true;
                    isFalling = false;
                    break;
                }
            }

            if(!cancelFall) {
                for(Pos& piece: fallingRock) {
                    piece.y -= 1;
                }
            }

            streamIndex = (streamIndex + 1) % input.size();

            //cycleDetection
            static long long lastMaxY = 0;
            static long long lastIndex = 0;
            static long long lastDeltaY = 0;
            static long long lastDeltaI = 0;
            if(streamIndex == 0) {
                long long deltaY = maxY - lastMaxY;
                long long deltaI = (i - lastIndex);

                static bool foundCycle = false;
                if(deltaY == lastDeltaY && deltaI == lastDeltaI && !foundCycle && deltaY > 0) {
                    foundCycle = true;

                    std::cout << std::endl << "detected cycle at rock " << i << ", skipping time" << std::endl;

                    long long piecesLeft = maxPieces - i;
                    long long wholeCyclesLeft = piecesLeft / deltaI;                    
                    i += wholeCyclesLeft * deltaI;

                    std::cout << "maxY increased from " << maxY;
                    long long yDiff = wholeCyclesLeft * deltaY;
                    maxY += yDiff;
                    std::cout << " to " << maxY << std::endl;

                    std::cout << "copying " << walls.size() << " rock pieces" << std::endl;

                    int r = 0;
                    for(Pos& pos: walls) {
                        pos.y += yDiff;
                        if(r % 2500 == 0 || r >= walls.size() - 2) std::cout << "  copying copying rock " << r << " from (" << pos.x << "  " << pos.y - yDiff<< ")" << " to (" << pos.x << "  " << pos.y << ")" << std::endl;
                        r++;
                    }

                    std::cout << "moving rock up" << std::endl;
                    for(Pos& piece: fallingRock) {
                        std::cout << "  from (" << piece.x << "  " << piece.y << ") to ";
                        piece.y += yDiff;
                        std::cout << "(" << piece.x << "  " << piece.y << ") " << std::endl;
                    }
                    std::cout << std::endl;

                    std::cout << "continuing with rock " << i << " with max " << maxY << std::endl;
                    deltaY = 0;
                    deltaI = 0;
                }

                lastMaxY = maxY;
                lastIndex = i;
                lastDeltaY = deltaY;
                lastDeltaI = deltaI;
            }
        }//while(isFalling)

        for(Pos piece: fallingRock) {
            walls.push_back(piece);
        }

        //update values

        long long localMaxY = Stream<Pos>::of(fallingRock).map<long long>([](const Pos& c){ return c.y; }).max().value_or(0);
        maxY = std::max(localMaxY, maxY);

        rockType = (rockType + 1) % 5;
    }
    print() << maxY;

    return 0;
}

void getRock(std::vector<Pos>& rockOut, int rockType, long long maxY) {
    if(rockType == 0) {
        rockOut.push_back({3, maxY + 4});
        rockOut.push_back({4, maxY + 4});
        rockOut.push_back({5, maxY + 4});
        rockOut.push_back({6, maxY + 4});
    } else if(rockType == 1) {
        rockOut.push_back({4, maxY + 4});
        rockOut.push_back({3, maxY + 5});
        rockOut.push_back({4, maxY + 5});
        rockOut.push_back({5, maxY + 5});
        rockOut.push_back({4, maxY + 6});
    } else if(rockType == 2) {
        rockOut.push_back({3, maxY + 4});
        rockOut.push_back({4, maxY + 4});
        rockOut.push_back({5, maxY + 4});
        rockOut.push_back({5, maxY + 5});
        rockOut.push_back({5, maxY + 6});
    } else if(rockType == 3) {
        rockOut.push_back({3, maxY + 4});
        rockOut.push_back({3, maxY + 5});
        rockOut.push_back({3, maxY + 6});
        rockOut.push_back({3, maxY + 7});
    } else if(rockType == 4) {
        rockOut.push_back({3, maxY + 4});
        rockOut.push_back({4, maxY + 4});
        rockOut.push_back({3, maxY + 5});
        rockOut.push_back({4, maxY + 5});
    }
}