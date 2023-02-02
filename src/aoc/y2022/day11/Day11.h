#ifndef DAY11_H
#define DAY11_H

#include "../Utils.h"
#include "../util/strings.h"
#include "../util/stream.h"
#include "../util/a_star.h"

#include <iostream>
#include <string>
#include <algorithm>

struct Operation {
    std::vector<std::string> operationElements{};

    long long evaluate(long long old) {
        std::string op1String{ operationElements.at(3) };
        long long op1 = (op1String == "old"? old: std::stoll(op1String));

        std::string op2String{ operationElements.at(5) };
        long long op2 = (op2String == "old"? old: std::stoll(op2String));

        if(operationElements.at(4) == "*") {
            return op1 * op2;
        }

        else {
            return op1 + op2;
        }
    }

};

struct Monkey {
    std::vector<long long> items{};
    Operation operation{};
    int test{};
    int throwWhenTrue{};
    int throwWhenFalse{};
    long long inspections{0};
};

Monkey paragraphToMonkey(const std::string& line);

#endif