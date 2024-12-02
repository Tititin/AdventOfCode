#pragma once

#include "FileParser.h"

bool checkIsSorted(const std::vector<int>& _floors, const t_Order& _order);
bool checkFloorDistance(const std::vector<int>& _floors);

bool analyzeAndRemoveOneLevel(const std::vector<int>& _floors);

void dayTwo(const bool& isPartTwo = false);
