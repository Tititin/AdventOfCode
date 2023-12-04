#pragma once

#ifndef DAYFOUR_H_
# define DAYFOUR_H_

#include "FileParser.h"

typedef struct					s_Card
{
	int							_id;

	std::vector<std::string>	_winNbs;
	std::vector<std::string>	_playerNbs;
}								t_Card;

int			calculateMatches(std::vector<std::string>& _winNbs, std::vector<std::string>& _playerNbs);

void		calculateMatchesPartTwo(unsigned int& finalValue, std::vector<t_Card>& _cards, std::vector<int>& _quantity);

void		dayFour(const bool& isPartTwo = false);

#endif // !DAYFOUR_H_
