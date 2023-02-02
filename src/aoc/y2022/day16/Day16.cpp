#include "Day16.h"

int main() {
    std::vector<std::string> input{};
    getLines(input, 2022, 16);

    //READ INPUT

    std::map<std::string, Point> stringToPoint{};
    std::vector<Point> allPoints{};

    for(const std::string& s: input) {
        std::vector<std::string> splitLine{};
        strings::split(splitLine, s, " ");
        std::string name{ splitLine.at(1) };
        int flowRate = std::stoi(splitLine.at(4).substr(5, splitLine.at(4).find(";") - 5));

        Point p{ name, flowRate };
        for(int i = 9; i < splitLine.size(); i++) {
            p.followingPoints.push_back(splitLine.at(i).substr(0, 2));
        }
        stringToPoint[name] = p;
        allPoints.push_back(p);
    }

    //CALCULATE PATHS

    std::map<std::tuple<std::string, std::string>, int> pathLengths{};
    for(int i = 0; i < allPoints.size(); i++) {
        for(int j = 0; j < allPoints.size(); j++) {
            if(i == j || allPoints.at(j).flowRate == 0) continue;
            Point p1{ allPoints.at(i) };
            Point p2{ allPoints.at(j) };

            pathLengths[{p1.name, p2.name}] = distance(stringToPoint, p1, p2);
        } 
    } 

    //Find relevant points
    std::vector<std::string> relevantPoints{
        Stream<Point>::of(allPoints)
        .filter([](const Point& p){ return p.flowRate > 0; })
        .map<std::string>([](const Point& p){ return p.name; })
        .toVector()
    };

    //part 1
    State start{"AA", 0, 0, relevantPoints};
    int out = -paths::a_star<State>(
        start,
        [&stringToPoint, &pathLengths](std::vector<State>& out, const State& cur){ generateStates(out, cur, stringToPoint, pathLengths, 30); },
        [](const State& cur){ 
            std::vector<State>ignored{}; 
            return isEnd(ignored, cur, 30); 
        },
        State::hash,
        true, false,
        [](const State& cur){ return std::to_string(cur.minutes) + " " + std::to_string(cur.totalPressure); }
    ).totalPressure;

    print() << out;

    //part 2
    std::vector<State> endStates{};
    paths::a_star<State>(
        start,
        [&stringToPoint, &pathLengths](std::vector<State>& out, const State& cur){ generateStates(out, cur, stringToPoint, pathLengths, 26); },
        [&endStates](const State& cur){ 
            return isEnd(endStates, cur, 26); 
        },
        State::hash,
        false, false,
        [](const State& cur){ return std::to_string(cur.minutes) + " " + std::to_string(cur.totalPressure); }
    );

    std::cout << "found " << endStates.size() << " states ending" << std::endl;

    out = 0;
    for(int i = endStates.size() - 1; i >= 0; i--) {
        for(int j = endStates.size() - 1; j >= i; j--) {
            if(i == j) continue;

            const State& end1{ endStates.at(i) };
            const State& end2{ endStates.at(j) };

            bool overlappingValves = false;
            for(const std::string& valve: end1.openPoints) {
                if(std::find(end2.openPoints.begin(), end2.openPoints.end(), valve) != end2.openPoints.end()) {
                    overlappingValves = true;
                    break;
                }
            }
            if(overlappingValves) continue;
            int thisScore = std::abs(end1.totalPressure) + std::abs(end2.totalPressure);
            if(thisScore > out) {
                out = thisScore;
                std::cout << "new max score " << out << std::endl;
            }
        }
    }
    print() << out;

    return 0;
}

//find distances

int distance(const std::map<std::string, Point>& stringToPoint, const Point& a, const Point& b) {
    return -paths::a_star<Path>(
        { a.name, 0 },
        [&stringToPoint](std::vector<Path>& out, const Path& cur){
            for(const std::string& follow: stringToPoint.at(cur.current).followingPoints) {
                out.push_back({ follow, cur.moves - 1 });
            }
        },
        [&b](const Path& cur){ return cur.current == b.name; },
        Path::hash,
        false
    ).moves;
}


//part 1


bool isEnd(std::vector<State>& endOut, const State& end, int MAX_MINUTE) {
    bool out = std::abs(end.minutes) >= MAX_MINUTE || end.openPoints.size() == 0;
    if(out) endOut.push_back(end);
    return out;
}

void generateStates(std::vector<State>& out, const State& current, std::map<std::string, Point>& stringToPoint, std::map<std::tuple<std::string, std::string>, int>& pathLengths, int MAX_MINUTE) {
    Point currentPoint{ stringToPoint.at(current.name) };
    if(std::abs(current.minutes) >= MAX_MINUTE) return;
    
    for(int i = current.openPoints.size() - 1; i >= 0; i--) {
        State nextState{current};

        std::string nextName{ nextState.openPoints.at(i) };
        Point nextPoint{ stringToPoint.at(nextName) };
        
        nextState.name = nextPoint.name;
        nextState.openPoints.erase(nextState.openPoints.begin() + i);

        int minuteAdvance = pathLengths.at({currentPoint.name, nextPoint.name}) + 1;    //travel time + 1 minute to open the valve
        nextState.minutes -= minuteAdvance;
        if(std::abs(nextState.minutes) < MAX_MINUTE) {
            nextState.totalPressure -= (MAX_MINUTE - std::abs(nextState.minutes)) * nextPoint.flowRate; //calculate total pressure this valve produces until minute 30 
        }

        out.push_back(nextState);
    }
}