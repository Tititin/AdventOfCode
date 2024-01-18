#pragma once

#include "DayTen.h"
#include "DaySixteen.h"
#include "FileParser.h"

unsigned long long int convertHexToDec(const std::string& _lengthHex);

void	updateDirection(const std::string& _word, t_Direction& _direction);

bool	checkLeft(const std::vector<std::string>& _digMap, const t_Pos& _pos);
bool	checkRight(const std::vector<std::string>& _digMap, const t_Pos& _pos);
bool	checkUp(const std::vector<std::string>& _digMap, const t_Pos& _pos);
bool	checkDown(const std::vector<std::string>& _digMap, const t_Pos& _pos);

void	dayEighteen(const bool& isPartTwo = false);
