#include "Day13.h"

int main() {
    std::vector<std::string> input{};
    getLines(input, 2022, 13);

    int out = 0;
    for(int i = 0, pairIndex = 1; i < input.size(); i+=3, pairIndex++) {
        const std::string& element1{ input.at(i) };
        const std::string& element2{ input.at(i + 1) };

        if(compare(element1, element2) == 1) out += pairIndex;
    }
    print() << out << std::endl;

    std::vector<std::string> sortedInput { Stream<std::string>::of(input)
        .filter([](const std::string& s){ return s.size() > 0; })
        .push("[[2]]")
        .push("[[6]]")
        .sort([](const std::string& s1, const std::string& s2){
            return compare(s1, s2) == 1;
        })
        .toVector()
    };

    int index1 = std::find(sortedInput.begin(), sortedInput.end(), "[[2]]") - sortedInput.begin() + 1;
    int index2 = std::find(sortedInput.begin(), sortedInput.end(), "[[6]]") - sortedInput.begin() + 1;

    print() << (index1 * index2); 
}

void splitCommaNotInBrace(std::vector<std::string>& out, std::string s) {
    std::string current{ "" };
    
    int braceLevel = 0;
    for(int i = 0; i < s.size(); i++) {
        char c = s.at(i);

        if(c == '[') braceLevel++;
        else if(c == ']') braceLevel--;

        if(c == ',' && braceLevel == 0) {
            out.push_back(current);
            current = "";
            continue;
        }

        current += c;
    }

    if(current.size() != 0) out.push_back(current);
}

int compare(const std::string& e1, const std::string& e2, int rekLevel) {
    if(e1.find("[") == 0 && e2.find("[") == 0) {
        std::vector<std::string> elementsFrom1{};
        splitCommaNotInBrace(elementsFrom1, e1.substr(1, e1.size() - 2));
        std::vector<std::string> elementsFrom2{};
        splitCommaNotInBrace(elementsFrom2, e2.substr(1, e2.size() - 2));

        for(int i = 0; i < std::min(elementsFrom1.size(), elementsFrom2.size()); i++) {
            int out = compare(elementsFrom1.at(i), elementsFrom2.at(i), rekLevel + 1);
            if(out == -1) return -1;
            if(out == 1) return 1;
        }
        int out = compare(elementsFrom1.size(), elementsFrom2.size());
        return out;
    }

    else if(e1.find("[") != 0 && e2.find("[") == 0) return compare("[" + e1 + "]", e2);
    else if(e1.find("[") == 0 && e2.find("[") != 0) return compare(e1, "[" + e2 + "]");
    else {
        int e1Int = std::stoi(e1);
        int e2Int = std::stoi(e2);
        return compare(e1Int, e2Int);
    }
}

int compare(int e1, int e2) {
    int out = (e2 > e1? 1: (e1 == e2? 0: -1));
    return out;
}