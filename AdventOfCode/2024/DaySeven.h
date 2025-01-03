#pragma once

#include "FileParser.h"

unsigned long long int	combineOperator(const unsigned long long int& _left, const unsigned long long int& _right);

unsigned long long int findAllOperations(const long long int& _nbToFind, const std::vector<unsigned long long int>& _numbers, const bool& isPartTwo = false);

void daySeven(const bool& isPartTwo = false);
