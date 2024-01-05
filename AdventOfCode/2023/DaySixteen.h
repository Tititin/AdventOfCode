#pragma once

#include "FileParser.h"

bool checkIfDirectionIsHorizontal(const t_Direction& _direction);
void turnRight(t_Direction& _direction);
void turnLeft(t_Direction& _direction);

bool isDividerNotUsed(const std::vector<t_Pos>& _usedDividers, const t_Pos& _pos);
bool checkAtLeastOneLaserIsRunning(const std::vector<bool>& _laserRunning);

void daySixteen(const bool& isPartTwo = false);