#include "Day04.h"

int main() {
    std::vector<std::string> input{};
    getLines(input, 2022, 04);

    Stream<std::vector<Range>> ranges {
        Stream<std::string>::of(input)
        .map<std::vector<std::string>>([](const std::string& line){ 
            std::vector<std::string> out{};
            strings::split(out, line, ",");
            return out; 
        })
        .map<std::vector<Range>>([](const std::vector<std::string>& lines){
            std::vector<Range> out{};
            for(const std::string& line: lines) {
                std::vector<std::string> lineParts{};
                strings::split(lineParts, line, "-");
                out.push_back(Range{ std::stoi(lineParts.at(0)), std::stoi(lineParts.at(1)), line });
            }
            return out;
        })
    };

    print() << ranges
    .countMatch([](int i, const std::vector<Range>& sections){
        return sections.at(0).fullyContains(sections.at(1)) || sections.at(1).fullyContains(sections.at(0));        
    });

    //part 2

    print() << ranges
    .countMatch([](int i, const std::vector<Range>& sections){
        return sections.at(0).partiallyContains(sections.at(1)) || sections.at(1).partiallyContains(sections.at(0));        
    });

    return 0;
}

bool Range::fullyContains(const Range& other) const {
    return lower <= other.lower && other.higher <= higher;
}

bool Range::partiallyContains(const Range& other) const {
    return (other.lower >= lower && other.lower <= higher) ||
        (other.higher >= lower && other.higher <= higher) ||
        (other.lower <= lower && other.higher >= higher);
}