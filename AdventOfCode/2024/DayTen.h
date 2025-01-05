#pragma once

#include "FileParser.h"
#include "utils.h"

typedef struct	s_TrailHead
{
	t_Pos		startPos;

	t_Pos		currentPos;

	std::vector<t_Pos>	nineFound;

	unsigned int	level = 0;
	unsigned int	score = 0;
}				t_TrailHead;

void	runTrail(t_TrailHead _trail, const std::vector<std::string>& _topoMap);

void	dayTen(const bool& isPartTwo = false);
