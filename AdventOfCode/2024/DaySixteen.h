#pragma once

#include "FileParser.h"
#include "utils.h"

typedef struct	s_MazeRunner
{
	t_Pos		currentPos;
	t_Direction	currentDirection = RIGHT;

	unsigned int	moveMalus = 0;

	t_Pos		endToReach;
}				t_MazeRunner;

void	runMaze(t_MazeRunner _runner, const std::vector<std::string>& _maze, std::vector<std::vector<long int>>& _distances);

void daySixteen(const bool& isPartTwo = false);
