#pragma once

#ifndef DAYTWO_H_
# define DAYTWO_H_

#include "FileParser.h"

typedef struct  s_bag
{
	int			red = 0;
	int			green = 0;
	int			blue = 0;
}				t_bag;

void	initBag(t_bag& _bag);

void	updateMinimumBag(t_bag& _bag, const int& _quantity, const std::string& _color);

void	resetMinimumBag(t_bag& _bag);

bool	checkCubeNumber(const int& _cubes, const std::string& _color, const t_bag& bag);

bool	checkIfNumber(const std::string& _word);

int		getGameID(const std::string& _string);

void	dayTwo(const bool& isPartTwo = false);

#endif /* DAYTWO_H_ */