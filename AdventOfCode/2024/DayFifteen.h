#pragma once

#include "FileParser.h"
#include "utils.h"

bool	pushBoxes(std::vector<std::string>& _boxesMap, const t_Pos& _robotPos, const t_Direction& _direction);
bool	pushBoxesPartTwo(std::vector<std::string>& _boxesMap, const t_Pos& _robotPos, const t_Direction& _direction);

void dayFifteen(const bool& isPartTwo = false);
