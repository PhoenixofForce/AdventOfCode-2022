#ifndef DAY04_H
#define DAY04_H

#include "../Utils.h"
#include "../util/strings.h"
#include "../util/stream.h"
#include "../util/a_star.h"

#include <iostream>
#include <string>
#include <algorithm>

struct Range {
    int lower{};
    int higher{};
    std::string line{};

    bool fullyContains(const Range& other) const;
    bool partiallyContains(const Range& other) const;
};

#endif