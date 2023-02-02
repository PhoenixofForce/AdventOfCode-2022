#include "Day01.h"

int main() {
    std::vector<std::string> input{};
    getParagraphs(input, 2022, 1);
    
    Stream<int> str = Stream<std::string>::of(input)
    .map<int>([](const std::string& s){     //Map to sum of calories
        std::vector<std::string> splitString{};
        strings::split(splitString, s, " ");

        return Stream<std::string>::of(splitString)
            .map<int>([](const std::string& s2){ return std::stoi(s2); })
            .sum(0);
     });

    print() << str.max().value_or(0);
    print(2) << str.sort().reverse().limit(3).sum(0);

    return 0;
}