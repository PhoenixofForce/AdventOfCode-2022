#ifndef DAY21_H
#define DAY21_H

#include "../Utils.h"
#include "../util/strings.h"
#include "../util/stream.h"
#include "../util/a_star.h"

#include <iostream>
#include <string>
#include <algorithm>

struct TreePiece{
    std::string name{};
    std::string left{};
    std::string op{};
    std::string right{};

    bool operator==(const TreePiece& left) const {
        return name == left.name;
    }

    bool operator<(const TreePiece& left) const {
        return name < left.name;
    }

    bool isLeaf() const {
        return op == "#";
    }

    long long getValue(const std::map<std::string, TreePiece>& pieces) const {
        if(op == "#") return std::stoll(left);
        
        long long rightV = pieces.at(right).getValue(pieces);
        long long out = pieces.at(left).getValue(pieces);
        if(op == "+") out += rightV;
        if(op == "-") out -= rightV;
        if(op == "*") out *= rightV;
        if(op == "/") out /= rightV;
        return out;
    }

    long long reverseUnknownLeft(const std::map<std::string, TreePiece>& pieces, long long top) const {
        if(op == "#") return std::stoll(left);
        
        long long rightV = pieces.at(right).getValue(pieces);
        std::cout <<  name << ": " << "l " << op << " " << rightV << " =soll= " << top << ", l=" << left << std::endl; 
        long long out = top;
        if(op == "+") out -= rightV;
        if(op == "-") out += rightV;
        if(op == "*") out /= rightV;
        if(op == "/") out *= rightV;
        return out;
    }

    long long reverseUnknownRight(const std::map<std::string, TreePiece>& pieces, long long top) const {
        if(op == "#") return std::stoll(left);
        
        long long leftV = pieces.at(left).getValue(pieces);
        std::cout << name << ": "  << leftV << " " << op << " r" << " =soll= " << top << ", r=" << right << std::endl; 
        long long out = 0;
        if(op == "+") out = top - leftV;
        if(op == "-") out = leftV - top;
        if(op == "*") out = top / leftV;
        if(op == "/") out = leftV / top;
        return out;
    }

    bool contains(const std::map<std::string, TreePiece>& pieces, const std::string& toContain) const {
        if(name == toContain) return true;
        if(isLeaf()) return false;
        return pieces.at(left).contains(pieces, toContain) || pieces.at(right).contains(pieces, toContain);
    }

    bool leftContains(const std::map<std::string, TreePiece>& pieces, const std::string& toContain) const {
        if(name == toContain || left == toContain) return true;
        if(isLeaf()) return false;
        return pieces.at(left).contains(pieces, toContain);
    }

    bool rightContains(const std::map<std::string, TreePiece>& pieces, const std::string& toContain) const {
        if(name == toContain ||right == toContain) return true;
        if(isLeaf()) return false;
        return pieces.at(right).contains(pieces, toContain);
    }
};

void buildOperationTree(std::vector<std::string> input, std::map<std::string, TreePiece>& values);

#endif