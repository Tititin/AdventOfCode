#pragma once

#ifndef DAYTHREE_H_
# define DAYTHREE_H_

#include "FileParser.h"

typedef struct	s_Coor
{
	int	x = 0;
	int y = 0;
}				t_Coor;

typedef struct	s_Gear
{
	int			x = 0;
	int			y = 0;

	int			number;

	bool		isChecked = false;
}				t_Gear;

bool						checkSymbolNearNumber(std::vector<std::string>& _map, const t_Coor& _start, const t_Coor& _end, std::vector<t_Gear>& _gears, const int& nbr, const bool& isPartTwo = false);

void						checkGears(std::vector<t_Gear>& _gears, int& finalValue);

std::vector<std::string>	initFileMap(FileParser& _fileParser);

void	dayThree(const bool& isPartTwo = false);

#endif // !DAYTHREE_H_
