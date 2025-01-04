#pragma once

#include "FileParser.h"

unsigned long long int	getRobotsInQuadrant(const std::vector<t_Pos>& _robots, const t_Pos& _northWest, const t_Pos& _southEast);

void	updateMap(std::vector<std::string>& _map, std::vector<t_Pos>& _robots);

void dayFourteen(const bool& isPartTwo = false);
