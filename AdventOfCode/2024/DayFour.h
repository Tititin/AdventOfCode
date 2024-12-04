#pragma once

#include "FileParser.h"

int		checkHorizontally(const std::string& _line, const t_Pos& _pos);
int		checkVertically(const std::vector<std::string>& _map, const t_Pos& _pos);
int		checkDiagonally(const std::vector<std::string>& _map, const t_Pos& _pos);
int		checkCross(const std::vector<std::string>& _map, const t_Pos& _pos);

void dayFour(const bool& isPartTwo = false);
