#pragma once

#include "FileParser.h"

bool	checkIfAllZero(std::vector<long long int>& line);

void	calcFinalValue(std::vector<std::vector<long long int> >& dataNumbers, long long int& finalValue, const bool& isPartTwo = false);

void	dayNine(const bool& isPartTwo = false);