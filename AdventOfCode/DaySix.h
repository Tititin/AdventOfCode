#pragma once

#include "FileParser.h"
#include <list>

bool checkMarkerValidity(const std::list<char>& marker, const int& requiredLength);

void daySix(bool isPartTwo = false);