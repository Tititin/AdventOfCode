#pragma once

#include "FileParser.h"
#include <vector>

typedef struct s_moveParams
{
	int quantity = 0;
	int srcPos = 0;
	int destPos = 0;
} t_moveParams;

void dayFive(bool isPartTwo = false);

void reverseStacks(std::vector<std::vector<char> >& stacks);
void doMove(std::vector<std::vector<char> >& stacks, const t_moveParams& moveParams, bool isPartTwo = false);