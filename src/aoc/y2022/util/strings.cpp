#include "strings.h"

#include <vector>
#include <string>
#include <regex>

namespace strings {

    void split(std::vector<std::string>& out, std::string toSplit, const std::regex& regex) {
        std::smatch match;
        while(std::regex_search(toSplit, match, regex)) {
            int splitPosition = match.position();
            out.push_back(toSplit.substr(0, splitPosition));
            toSplit = toSplit.substr(splitPosition + match.length());
        }

        if(!toSplit.empty()) out.push_back(toSplit);
    }

    void split(std::vector<std::string>& out, std::string toSplit, const std::string& delim) {
        size_t pos = 0;
        std::string token;

        while((pos = toSplit.find(delim)) != std::string::npos) {
            token = toSplit.substr(0, pos);

            out.push_back(token);

            toSplit.erase(0, pos + delim.size());
        }
        if(toSplit.length() > 0) {
            out.push_back(toSplit);
        }
    }

    std::string& trim(std::string& str) {
        std::regex r("(^\\s+|\\s+$)");
        str = std::regex_replace(str, r, "");
        return str;
    }  

    void toVector(std::vector<char>& out, const std::string& string) {
        for(char c: string) {
            out.push_back(c);
        }
    }

    std::vector<char> toVector(const std::string& string) {
        std::vector<char> out{};
        toVector(out, string);
        return out;
    }

    std::string fromVector(const std::vector<char>& in) {
        std::string out{};
        for(char c: in) out += c;
        return out;
    }
}