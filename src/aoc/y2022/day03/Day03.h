#ifndef DAY03_H
#define DAY03_H

#include "../Utils.h"
#include "../util/strings.h"
#include "../util/stream.h"
#include "../util/a_star.h"
#include "../util/sets.h"

#include <iostream>
#include <string>
#include <set>
#include <algorithm>

int getPriority(const std::string& sack);
int getStringPriority(const std::string& s);
int getCharPriority(const char& c);

#endif