#ifndef STRINGS_H
#define STRINGS_H

#include <vector>
#include <string>
#include <regex>

namespace strings {

    void split(std::vector<std::string>& out, std::string toSplit, const std::regex& regex);
    void split(std::vector<std::string>& out, std::string toSplit, const std::string& delim);
    std::string& trim(std::string& str);
    void toVector(std::vector<char>& out, const std::string& string);
    std::vector<char> toVector(const std::string& string);
    std::string fromVector(const std::vector<char>& in);
}

#endif