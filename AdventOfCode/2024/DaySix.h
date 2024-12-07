#pragma once

#include "FileParser.h"

bool	checkIfUnique(const t_Pos& _pos, const std::vector<t_Pos>& _visited);

void	moveOneTile(t_Pos& _pos, t_Direction& _direction, const std::vector<std::string>& _labMap);

void daySix(const bool& isPartTwo = false);
