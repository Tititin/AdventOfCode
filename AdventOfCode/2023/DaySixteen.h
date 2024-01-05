#pragma once

#include "FileParser.h"

void prepareNewRun(std::vector<std::string>& energizedMap, std::vector<t_Pos>& laserPos, std::vector<t_Direction>& laserDirections, std::vector<bool>& laserRunning, std::vector<t_Pos>& usedDividers, unsigned int& finalValue);

bool checkIfDirectionIsHorizontal(const t_Direction& _direction);
void turnRight(t_Direction& _direction);
void turnLeft(t_Direction& _direction);

bool isDividerNotUsed(const std::vector<t_Pos>& _usedDividers, const t_Pos& _pos);
bool checkAtLeastOneLaserIsRunning(const std::vector<bool>& _laserRunning);

void energizeMap(std::vector<std::string>& laserMap, std::vector<std::string>& energizedMap, std::vector<t_Pos>& laserPos, std::vector<t_Direction>& laserDirections, std::vector<bool>& laserRunning, std::vector<t_Pos>& usedDividers, unsigned int& finalValue);
void daySixteen(const bool& isPartTwo = false);