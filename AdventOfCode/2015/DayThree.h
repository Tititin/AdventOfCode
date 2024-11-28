#pragma once

#include "FileParser.h"

//typedef struct	s_Pos
//{
//	int x;
//	int y;
//}				t_Pos;

bool	isHouseAlreadyVisited(const std::vector<t_Pos>& houses, const t_Pos& pos);

void	dayThree(const bool& isPartTwo = false);