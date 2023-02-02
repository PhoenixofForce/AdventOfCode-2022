#include "Day02.h"

int main() {
    std::vector<std::string> input{};
    getLines(input, 2022, 2);

    print() << Stream<std::string>::of(input)
    .map<int>(calcScore)
    .sum(0);

    print(2) << Stream<std::string>::of(input)
    .map<int>(calcScorePart2)
    .sum(0);

    return 0;
}

int calcScore(const std::string& line) {
    std::vector<std::string> splitLine{};
    strings::split(splitLine, line, " ");

    int score = 0;

    if(splitLine[1] == "X") score += 1;
    else if(splitLine[1] == "Y") score += 2;
    else if(splitLine[1] == "Z") score += 3;

    if(line == "A Z" || line == "B X" || line == "C Y") score += 0;
    else if(line == "A X" || line == "B Y" || line == "C Z") score += 3;
    else score += 6;

    return score;
}

int calcScorePart2(const std::string& line) {
    std::vector<std::string> splitLine{};
    strings::split(splitLine, line, " ");

    int score = 0;

    if(splitLine[1] == "X") {   //loose
        score += 0;

        if(splitLine[0] == "B") score += 1;
        else if(splitLine[0] == "C") score += 2;
        else score += 3;
    }

    else if(splitLine[1] == "Y") {   //draw
        score += 3;
        
        if(splitLine[0] == "A") score += 1;
        else if(splitLine[0] == "B") score += 2;
        else score += 3;
    }

    else if(splitLine[1] == "Z") {   //win
        score += 6;

        if(splitLine[0] == "C") score += 1;
        else if(splitLine[0] == "A") score += 2;
        else score += 3;
    }

    return score;
}