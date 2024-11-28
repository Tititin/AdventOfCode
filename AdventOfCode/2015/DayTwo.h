#pragma once

#include "FileParser.h"

unsigned long long int		findSmallestAreaSize(const std::vector<int>& _dimensions);
unsigned long long int		findSmallestPerimeterSize(const std::vector<int>& _dimensions);
unsigned long long int		calcBow(const std::vector<int>& _dimensions);

void	dayTwo(const bool& isPartTwo = false);
