#pragma once

#include "FileParser.h"

bool vowelsCheck(const std::string& _str);
bool doubleLetterCheck(const std::string& _str);
bool forbiddenStringsCheck(const std::string& _str);

bool doublePairLetters(const std::string& _str);
bool doubleLetterWithOneBetweenCheck(const std::string& _str);

void dayFive(const bool& isPartTwo = false);
