#include "Day15.h"

int main() {
    std::vector<Sensor> input{};
    getLines(input, 2022, 15, stringToSensor);

    std::vector<Pos> blockedPositions{
        Stream<Sensor>::of(input)
        .flatten<Pos>([](const Sensor& s){ 
            std::vector<Pos> out{};
            out.push_back(s.sensorPos);
            out.push_back(s.closestBeacons);
            return out;
        })
        .toVector()
    };

    int desiredY = 2000000;
    std::unordered_set<Pos> unpossibleBeaconPositions{};
    for(Sensor& s: input) {
        int distanceToBeacon = s.sensorPos.distance(s.closestBeacons);

        for(int x = s.sensorPos.x - distanceToBeacon; x <= s.sensorPos.x + distanceToBeacon; x++) {
            Pos thisPos{x, desiredY};
            if(s.sensorPos.distance(thisPos) <= distanceToBeacon && 
                    std::find(blockedPositions.begin(), blockedPositions.end(), thisPos) == blockedPositions.end() &&
                    unpossibleBeaconPositions.find(thisPos) == unpossibleBeaconPositions.end()) {

                unpossibleBeaconPositions.insert(thisPos);
            }
        }
    }

    print() << unpossibleBeaconPositions.size() << std::endl;

    bool foundOut = false;
    for(int y = 0; y < 4000000; y++) {
        if(foundOut) break;
        for(int x = 0; x < 4000000; x++) {
            if(foundOut) break;

            Pos thisPos{x, y};
            bool foundSensor = false;

            for(const Sensor& s: input) {
                if(s.sensorPos.distance(thisPos) <= s.sensorPos.distance(s.closestBeacons)) {
                    int sensorRadiusAtRow = (s.sensorPos.distance(s.closestBeacons) - std::abs(y - s.sensorPos.y));
                    int xTo = s.sensorPos.x + sensorRadiusAtRow;

                    int xOffset = xTo - x;
                    x+= xOffset;

                    foundSensor = true;
                    break;
                }
            }

            if(foundSensor) continue;
            foundOut = true;
            long long out = x;
            out *= 4000000;
            out += y;
            print() << out << std::endl;
        }
    }

    return 0;
}

Sensor stringToSensor(const std::string& line) {
    std::vector<std::string> splitLine{};
    strings::split(splitLine, line, " ");
    int x = std::stoi(splitLine.at(2).substr(2, splitLine.at(2).length()-3));
    int y = std::stoi(splitLine.at(3).substr(2, splitLine.at(3).length()-3));

    int beaconX = std::stoi(splitLine.at(8).substr(2, splitLine.at(8).length()-3));
    int beaconY = std::stoi(splitLine.at(9).substr(2, splitLine.at(9).length()-2));

    return Sensor {x, y, beaconX, beaconY};
}

size_t std::hash<Pos>::operator()(const Pos& state) const { 
    size_t out = 17;
    out = out * 31 + state.x;
    out = out * 31 + state.y;
    return out;
} 