#pragma once

#include "FileParser.h"

void	sortVector(std::vector<size_t>& _positions);
void	reduceMap(std::map<char, std::vector<size_t>>& _mapPositions);

void	dayThree(const bool& isPartTwo = false);
