#include "Day11.h"

int main() {
    bool part2 = true;

    std::vector<Monkey> monkeys{};
    getParagraphs(monkeys, 2022, 11, paragraphToMonkey);

    long long commonTest = Stream<Monkey>::of(monkeys)
                    .map<long long>(&Monkey::test)
                    .reduce<long long>(1, [](long long r, long long c){ return r*c; });

    int rounds = part2? 10000: 20;
    for(int i = 0; i < rounds; i++) {
        for(Monkey& m: monkeys) {
            for(long long item: m.items) {
                m.inspections++;

                long long newValue = m.operation.evaluate(item);
                if(!part2) newValue /= 3;
                newValue %= commonTest; //to prevent overflow

                bool test = newValue % m.test == 0;
                int nextMonkey = test? m.throwWhenTrue: m.throwWhenFalse;
                monkeys.at(nextMonkey).items.push_back(newValue);
            }

            m.items.clear();
        }
    }

    print(part2) << Stream<Monkey>::of(monkeys)
    .map<long long>(&Monkey::inspections)
    .sort(std::greater<long long>())
    .limit(2)
    .reduce<long long>(1, [](long long r, long long c){ return r*c; });

    return 0;
}

Monkey paragraphToMonkey(const std::string& line) {
    std::string s = std::regex_replace(line, std::regex ("( |,)+"), " ");
    std::cout << s << std::endl;

    Monkey m{};

    std::vector<std::string> splitString{};
    strings::split(splitString, s, " ");

    int i = 4;
    for(i = 4; i < splitString.size(); i++) {
        if(splitString.at(i) == "Operation:") break;
        m.items.push_back(std::stoi(splitString.at(i)));
    }
    
    m.operation.operationElements = { splitString.at(i), splitString.at(i + 1), splitString.at(i + 2), splitString.at(i + 3), splitString.at(i + 4), splitString.at(i + 5) };
    m.test = std::stoi(splitString.at(i + 9));
    m.throwWhenTrue = std::stoi(splitString.at(i + 15));
    m.throwWhenFalse = std::stoi(splitString.at(i + 21));

    return m;
}