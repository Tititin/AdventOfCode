#pragma once

#include "FileParser.h"

typedef struct					s_BrickCoorXY
{
	unsigned int				x = 0;
	unsigned int				y = 0;
}								t_BrickCoorXY;

typedef struct					s_Point
{
	unsigned int				x = 0;
	unsigned int				y = 0;
	unsigned int				z = 0;
}								t_Point;

typedef struct					s_Brick
{
	unsigned int				id;

	std::vector<t_BrickCoorXY>	coorXY;
	int							z = 0;

	std::vector<unsigned int>	bricksAbove;
	std::vector<unsigned int>	bricksBelow;
}								t_Brick;

t_Brick	createBrick(const t_Point& _start, const t_Point& _end);
t_Brick	createHorizontalXBrick(const t_Point& _start, const t_Point& _end);
t_Brick	createHorizontalYBrick(const t_Point& _start, const t_Point& _end);
t_Brick createVerticalBrick(const t_Point& _start, const t_Point& _end);

void	moveBelow(t_Brick& brick);

void	dayTwentyTwo(const bool& isPartTwo = false);