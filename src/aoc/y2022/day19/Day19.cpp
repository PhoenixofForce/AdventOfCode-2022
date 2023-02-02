#include "Day19.h"

int main() {
    std::vector<Blueprint> input{};
    getLines(input, 2022, 19, Blueprint::fromString);
    
    //part1 - around 5 mins, part2 more like 15

    int out = 0;
    for(int i = 0; i < input.size(); i++) {
        int most = findMostGeodes(input.at(i), 24);
        std::cout << "blueprint " << i << " found " << most << " geodes" << std::endl;
        out += (i+1) * most;
    }
    print() << out << std::endl;

    out = Stream<Blueprint>::of(input)
    .limit(3)
    .map<int>([](const Blueprint& b){ return findMostGeodes(b, 32); })
    .reduce<int>(1, [](int& res, const int& e){ return res*e; });
    print() << out;

    return 0;
}

int findMostGeodes(const Blueprint& print, int maxMin) {
    return -paths::a_star<State>(
        State{},
        [&print](std::vector<State>& statesOut, const State& current){ advanceStates(statesOut, print, current); },
        [&maxMin](const State& cur){ return isEnd(cur, maxMin); },
        State::hash,
        false, false,
        [](const State& current){ return std::to_string(current.minutes) + "min, " + std::to_string(current.geodes) + "geodes"; },
        [](const State& best, const State& current) {
            int minuteDiff = std::abs(best.minutes - current.minutes) - 1;
            int totalGeodesToBuild = (minuteDiff * (minuteDiff + 1)) / 2 + minuteDiff * current.geodeRobot;
            return std::abs(current.geodes) + totalGeodesToBuild < std::abs(best.geodes);
        }
    ).geodes;
}

bool isEnd(const State& end, int MAXMIN) {
    return std::abs(end.minutes) >= MAXMIN;
}

void advanceStates(std::vector<State>& statesOut, Blueprint print, const State& current) {
    State newState{ current };
    newState.ores -= newState.oreRobot;
    newState.clays -= newState.clayRobot;
    newState.obsidians -= newState.obsidianRobot;
    newState.geodes -= newState.geodeRobot;
    newState.minutes -= 1;

    int maxOreCost = std::max(print.oreCostForOre, std::max(print.oreCostForClay, std::max(print.oreCostForObsidian, print.oreCostForGeode)));

    bool enoughOreForGeode = -current.ores >= print.oreCostForGeode;
    bool enoughObsidianForGeode = -current.obsidians >= print.obsidianCostForGeode;
    
    bool enoughOreForObsidian = -current.ores >= print.oreCostForObsidian;
    bool enoughClayForObsidian = -current.clays >= print.clayCostForObsidian;

    bool enoughOreForClay = -current.ores >= print.oreCostForClay;
    bool enoughOreForOre = -current.ores >= print.oreCostForOre;

    if(enoughObsidianForGeode && enoughOreForGeode) {
        State out{ newState };
        out.geodeRobot += 1;
        out.ores += print.oreCostForGeode;
        out.obsidians += print.obsidianCostForGeode;
        statesOut.push_back(out);
        return;
    }


    if(!(enoughObsidianForGeode && !enoughOreForGeode) || 
        false) {

        if(enoughClayForObsidian && enoughOreForObsidian && current.obsidianRobot < print.obsidianCostForGeode) {
            State out{ newState };
            out.obsidianRobot += 1;
            out.ores += print.oreCostForObsidian;
            out.clays += print.clayCostForObsidian;
            statesOut.push_back(out);
        }

        if(enoughOreForClay && current.clayRobot < print.clayCostForObsidian) {
            State out{ newState };
            out.clayRobot += 1;
            out.ores += print.oreCostForClay;
            statesOut.push_back(out);
        }

        if(enoughOreForOre && current.oreRobot < maxOreCost) {
            State out{ newState };
            out.oreRobot += 1;
            out.ores += print.oreCostForOre;
            statesOut.push_back(out);
        }
    }
        
    statesOut.push_back(newState);
}