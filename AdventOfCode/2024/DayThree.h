#pragma once

#include <iterator>
#include <regex>

#include "FileParser.h"

typedef struct	s_SafeZones
{
	std::size_t	start;
	std::size_t end;
}				t_SafeZones;

void		cleanZonesVectors(std::vector<std::size_t>& doTriggers, std::vector<std::size_t>& dontTriggers);

bool		checkIfInSafeZone(const size_t& pos, const std::vector<t_SafeZones>& safeZones);
std::string	checkIfMulExpression(int pos, const std::string& str);

unsigned long int	verifyAndMultiply(const std::string& _s);

void dayThree(const bool& isPartTwo = false);
