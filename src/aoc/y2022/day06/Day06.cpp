#include "Day06.h"

int main() {
    std::string input{ getFile(2022, 06) };

    bool part2 = false;
    int distinctSizeToLookFor = part2? 14: 4;

    std::vector<char> buffer{};
    for(int i = 0; i < distinctSizeToLookFor; i++) {
        buffer.push_back(input.at(i));
    }

    for(int i = distinctSizeToLookFor; i < input.length(); i++) {
        if(Stream<char>::of(buffer).distinct().size() == distinctSizeToLookFor) {
            print(part2) << i;
            break;
        }

        buffer.erase(buffer.begin());
        buffer.push_back(input.at(i));
    }

    return 0;
}