#pragma once

#include "FileParser.h"

typedef enum	e_SymetryType
{
	HORIZONTAL = 0,
	VERTICAL
}				t_SymetryType;

typedef struct	s_RegisteredSymetry
{
	t_SymetryType	symetry;
	int				line;
	int				row;
	int				column;
}				t_RegisteredSymetry;

int	getNbDifferentCharacters(const std::string& _s1, const std::string& _s2);

void dayThirteen(const bool& isPartTwo = false);