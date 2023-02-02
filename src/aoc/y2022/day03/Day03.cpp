#include "Day03.h"

int main() {
    std::vector<std::string> items{};
    getLines(items, 2022, 3);

    print() << Stream<std::string>::of(items)
    .map<int>(getPriority)
    .sum(0);

    print(2) << Stream<std::string>::of(items)
    .group(3)
    .map<std::string>([](const std::vector<std::string>& threeBags){
        std::vector<char> bagIntersection{};
        sets::intersectSets(bagIntersection, strings::toVector(threeBags.at(0)), strings::toVector(threeBags.at(1)));
        sets::intersectSets(bagIntersection, strings::toVector(threeBags.at(2)));

        return strings::fromVector(bagIntersection); 
    })
    .map<int>(getStringPriority)
    .sum(0);

    return 0;
}

int getPriority(const std::string& sack) {
    int itemCount = sack.size() / 2;
    std::string firstCompartment{ sack.substr(0, itemCount) };
    std::string secondCompartment{ sack.substr(itemCount) };

    std::vector<char> intersection{};
    sets::intersectSets(intersection, strings::toVector(firstCompartment), strings::toVector(secondCompartment));

    return getStringPriority(strings::fromVector(intersection));
}

int getStringPriority(const std::string& s) {
    int out = 0;
    for(char c: s) {
        out += getCharPriority(c);
    }
    return out;
}

int getCharPriority(const char& c) {
    if(c >= 'A' && c <= 'Z') {
        return c - 'A' + 27; 
    }

    if(c >= 'a' && c <= 'z') {
        return c - 'a' + 1; 
    }

    return 0;
}