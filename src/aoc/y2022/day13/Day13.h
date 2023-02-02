#ifndef DAY13_H
#define DAY13_H

#include "../Utils.h"
#include "../util/strings.h"
#include "../util/stream.h"
#include "../util/a_star.h"

#include <iostream>
#include <string>
#include <algorithm>

void splitCommaNotInBrace(std::vector<std::string>& out, std::string s);

int compare(const std::string& e1, const std::string& e2, int rekLevel = 0);
int compare(int e1, int e2);

#endif