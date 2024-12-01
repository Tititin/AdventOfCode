#pragma once

#include "FileParser.h"

void sortVector(std::vector<int>& list, const t_Order& _order);
void sortVectorAsc(std::vector<int>& list);
void sortVectorDesc(std::vector<int>& list);

unsigned int	findOccurences(const int& _number, const std::vector<int>& _list);

void dayOne(const bool& isPartTwo = false);
