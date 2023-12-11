#pragma once

#include "FileParser.h"

typedef struct	s_GalaxyPos
{
	int			x;
	int			y;
}				t_GalaxyPos;

typedef struct	s_EmptyData
{
	int			rows;
	int			columns;
}				t_EmptyData;

bool	checkIfEmptyRow(const std::string& _row);
bool	checkIfEmptyColumn(const std::vector<std::string>& _map, const int& _x);

t_EmptyData		countEmptyRowsAndColumns(const std::vector<int>& _emptyRows, const std::vector<int>& _emptyColumns, const t_GalaxyPos& _galaxyA, const t_GalaxyPos& _galaxyB);

void	dayEleven(const bool& isPartTwo = false);