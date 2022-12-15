#pragma once

#include "FileParser.h"
#include <vector>

void dayFour(bool isPartTwo = false);

std::vector<int>	cutZones(const std::string& section);
bool				checkIfFullyOverlappingZones(const std::vector<int>& section1, const std::vector<int>& section2);
bool				checkIfPartiallyOverlappingZones(const std::vector<int>& section1, const std::vector<int>& section2);