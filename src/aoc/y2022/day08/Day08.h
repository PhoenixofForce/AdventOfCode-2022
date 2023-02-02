#ifndef DAY08_H
#define DAY08_H

#include "../Utils.h"
#include "../util/strings.h"
#include "../util/stream.h"
#include "../util/a_star.h"

#include <iostream>
#include <string>
#include <algorithm>

bool isLeftEdgeVisible(const std::vector<std::string> map, int x, int y);
bool isRightEdgeVisible(const std::vector<std::string> map, int x, int y);
bool isTopEdgeVisible(const std::vector<std::string> map, int x, int y);
bool isBottomEdgeVisible(const std::vector<std::string> map, int x, int y);

int getLeftVisibleCount(const std::vector<std::string> map, int x, int y);
int getRightVisibleCount(const std::vector<std::string> map, int x, int y);
int getTopVisibleCount(const std::vector<std::string> map, int x, int y);
int getBottomVisibleCount(const std::vector<std::string> map, int x, int y);

int getValue(const std::vector<std::string> map, int x, int y);

#endif