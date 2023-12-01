#pragma once

#include "FileParser.h"
#include <vector>

void	dayTwo();

int		calcScore(const std::string& opponentMove, const std::string& playerMove, bool isPartTwo = false);
int		calcWin(const std::string& opponentMove, const std::string& playerMove);
int		calcDraw(const std::string& opponentMove, const std::string& playerMove);