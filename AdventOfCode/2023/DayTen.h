#pragma once

#include "FileParser.h"

typedef enum	e_TileType
{
	UNKNOWN,
	PIPE,
	OUTSIDE,
	INSIDE
}				t_TileType;

bool	checkIfPipeline(const std::vector<t_Pos>& _pipePos, const t_Pos& _pos);
bool	checkOutsideV2(const std::vector<std::string> _pipelineMap, const std::vector<t_Pos>& _pipePos, const t_Pos& _pos);

void	updateDirection(const char& _pipe, t_Direction& direction);

void	dayTen(const bool& isPartTwo = false);