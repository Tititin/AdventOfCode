#pragma once

#include "FileParser.h"

t_Pos& operator-(const t_Pos& left, const t_Pos& right);
t_Pos& operator+(const t_Pos& left, const t_Pos& right);

bool isAntinodeUnique(const t_Pos& _pos, const std::vector<t_Pos>& _antinodes);

void dayEight(const bool& isPartTwo = false);