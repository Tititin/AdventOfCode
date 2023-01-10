#pragma once

#include "FileParser.h"
#include <list>
#include <Windows.h>

typedef struct s_Pos
{
	int		x;
	int		y;
} t_Pos;

t_Pos calcTranslationVector(const t_Pos& start, const t_Pos& end);

void checkAndAddPosition(std::list<t_Pos>& visitedPos, t_Pos pos);

void moveHead(std::list<t_Pos>& visitedPos, t_Pos& headPos, t_Pos& tailPos, const std::string& direction, const int& length);
void moveHead(std::list<t_Pos>& visitedPos, t_Pos ropePos[], const std::string& direction, const int& length);

void dayNine(bool isPartTwo = false);