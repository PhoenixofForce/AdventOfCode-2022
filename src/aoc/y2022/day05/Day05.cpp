#include "Day05.h"

int main() {
    std::vector<std::string> input{};
    getLines(input, 2022, 05);

    bool part2 = false;

    //parse input
    std::vector<std::vector<char>> stacks{};
    for(std::string& s: input) {
        if(s.at(1) == '1') break;

        for(int i = 0; i < s.size(); i++) {
            int stackPos = (i - 1) / 4;
            if((i - 1) % 4 == 0) {
                char c = s.at(i);
                if(c == ' ') continue;
                while(stackPos >= stacks.size()) stacks.push_back({});
                stacks.at(stackPos).push_back(c);
            }
        } 
    }

    //run simultion
    for(std::string& s: input) {
        if(s.find("move") == std::string::npos) continue;
        std::vector<std::string> tasks{};
        strings::split(tasks, s, " ");

        int cratesToMove = std::stoi(tasks.at(1));
        int cratesFrom = std::stoi(tasks.at(3)) - 1;
        int cratesTo = std::stoi(tasks.at(5)) - 1;

        std::vector<char>& stackFrom{ stacks.at(cratesFrom) };
        std::vector<char>& stackTo{ stacks.at(cratesTo) };

        for(int i = cratesToMove - 1; i >= 0; i--) {
            int positionOffset = (part2? i: 0);
            char c = stackFrom.at(positionOffset);
            stackFrom.erase(stackFrom.begin() + positionOffset);
            stackTo.insert(stackTo.begin(), c);
        }
    }
    

    print(part2);
    for(const std::vector<char>& stack: stacks) {
        std::cout << stack.at(0);
    }


    return 0;
}