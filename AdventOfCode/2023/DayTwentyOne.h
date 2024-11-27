#pragma once

#include "FileParser.h"

typedef enum	e_GardenTileType
{
	EMPTY,
	ROCK,
	EVEN,
	ODD
}				t_GardenTileType;

void	updateTile(std::vector<std::vector<t_GardenTileType>>& _garden, t_Pos& _pos, unsigned int _steps);

void	dayTwentyOne(const bool& isPartTwo = false);