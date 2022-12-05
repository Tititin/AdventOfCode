#pragma once

#include "FileParser.h"
#include <vector>

void	dayThree(bool isPartTwo = false);

int		calcPriority(const char& c);
int		findAndCalcPriority(const std::string& sOne, const std::string& sTwo);
int		findAndCalcPriority(const std::string& sOne, const std::string& sTwo, const std::string& sThree);