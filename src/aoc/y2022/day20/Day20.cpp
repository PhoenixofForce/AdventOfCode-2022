#include "Day20.h"

int main() {

    bool part2 = true;
    std::vector<std::string> input{};
    getLines(input, 2022, 20);

    std::vector<value> values{};
    for(int i = 0; i < input.size(); i++) {
        values.push_back({i, std::stoi(input.at(i)) * (part2? 811589153ll: 1ll)});
    }

    for(int loop = 0; loop < (part2? 10: 1); loop++) {
        for(int i = 0; i < input.size(); i++) {
            int index = std::distance(values.begin(), std::find_if(values.begin(), values.end(), [&i](const value& v){ return v.originalIndex == i; }));
            long long toMove = values.at(index).value;
            values.erase(values.begin() + index);
            
            long long newIndex = index + toMove;
            if(newIndex <= 0) newIndex += values.size() * std::abs(std::floor(1.0 * newIndex / values.size())); //short version of while(i<0) i+=max
            newIndex %= values.size();

            
            values.insert(values.begin() + newIndex, {i, toMove});
        }
    }

    int indexOfZero = std::distance(values.begin(), std::find_if(values.begin(), values.end(), [](const value& v){ return v.value == 0; }));

    long long out = values.at((indexOfZero + 1000) % values.size()).value + values.at((indexOfZero + 2000) % values.size()).value + values.at((indexOfZero + 3000) % values.size()).value;
    print() << out;

    return 0;
}