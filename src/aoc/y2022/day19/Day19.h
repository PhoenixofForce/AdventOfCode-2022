#ifndef DAY19_H
#define DAY19_H

#include "../Utils.h"
#include "../util/strings.h"
#include "../util/stream.h"
#include "../util/a_star.h"

#include <iostream>
#include <string>
#include <algorithm>

struct Blueprint {
    int oreCostForOre{};
    int oreCostForClay{};
    int oreCostForObsidian{};
    int clayCostForObsidian{};
    int oreCostForGeode{};
    int obsidianCostForGeode{};

    static Blueprint fromString(const std::string& s) {
        std::vector<std::string> splitString{};
        strings::split(splitString, s, " ");
        
        Blueprint out{};
        out.oreCostForOre = std::stoi(splitString.at(6));
        out.oreCostForClay = std::stoi(splitString.at(12));
        out.oreCostForObsidian = std::stoi(splitString.at(18));
        out.clayCostForObsidian = std::stoi(splitString.at(21));
        out.oreCostForGeode = std::stoi(splitString.at(27));
        out.obsidianCostForGeode = std::stoi(splitString.at(30));
        return out;
    }
};

struct State {
    int oreRobot{ 1 };
    int clayRobot{};
    int obsidianRobot{};
    int geodeRobot{};
    
    int ores{};
    int clays{};
    int obsidians{};
    int geodes{};

    int minutes{}; 

    bool operator==(const State& rhs) const { 
        return oreRobot == rhs.oreRobot && 
            clayRobot == rhs.clayRobot &&
            obsidianRobot == rhs.obsidianRobot &&
            geodeRobot == rhs.geodeRobot &&
            ores == rhs.ores &&
            clays == rhs.clays &&
            obsidians == rhs.obsidians &&
            geodes == rhs.geodes &&
            minutes ==  rhs.minutes
            ;
    }
    
    bool operator<(const State& rhs) const { 
        return geodes < rhs.geodes || (geodes == rhs.geodes && minutes < rhs.minutes);
    }

    bool operator>(const State& rhs) const { 
        return geodes > rhs.geodes || (geodes == rhs.geodes && minutes > rhs.minutes);
    }

    static size_t hash(const State& state) {
        size_t out = 17;
        out = out * 31 + state.oreRobot;
        out = out * 31 + state.clayRobot;
        out = out * 31 + state.obsidianRobot;
        out = out * 31 + state.geodeRobot;
        out = out * 31 + state.ores;
        out = out * 31 + state.clays;
        out = out * 31 + state.obsidians;
        out = out * 31 + state.geodes;
        out = out * 31 + state.minutes;
        return out;
    }
};

int findMostGeodes(const Blueprint& print, int MAXMIN);

bool isEnd(const State& end, int maxMin);
void advanceStates(std::vector<State>& statesOut, Blueprint print, const State& current);

#endif