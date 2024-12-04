#pragma once

#include <iterator>
#include <regex>

#include "FileParser.h"

bool	checkIfMulExpression(int pos, const std::string& str);

unsigned long int	verifyAndMultiply(const std::string& _s);

void dayThree(const bool& isPartTwo = false);
