#pragma once

#include "FileParser.h"

typedef struct	s_Room
{
	std::string	name;

	std::string	left;
	std::string	right;
}				t_Room;

unsigned long long int	calcPPCM(unsigned long long int& a, unsigned long long int& b);

bool	checkIDs(const std::vector<int>& _ids, const std::vector<t_Room>& _rooms);
bool	checkIDs(const int& _id, const std::vector<int>& _ends);

void dayEight(const bool& isPartTwo = false);