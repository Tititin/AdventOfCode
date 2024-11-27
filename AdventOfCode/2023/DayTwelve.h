#pragma once

#include "FileParser.h"

void							displayVector(const std::vector<int>& _vector);

std::string						changePatternPartTwo(const std::string& _oldPattern, std::vector<int>& _groups);

std::vector<std::vector<int>>	calculateCombinations(int n, int r, std::vector<int> _groupsSizes);
std::vector<int>				retrieveGroups(const std::string& _groupStr);
int								getTotalFilledSquares(const std::vector<int>& _groups);

bool							isPossibleCombination(const std::vector<int>& _pattern, const std::vector<int>& _combination);
int								calculatePossibleCombinations(std::vector<std::vector<int>>& _combinations, const std::string& _pattern, std::vector<int> _groupsSize);

void	dayTwelve(const bool& isPartTwo = false);