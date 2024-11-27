#pragma once

#include "FileParser.h"
#include <queue>

typedef struct		s_DirectionPolicy
{
	unsigned short	left = 0;
	unsigned short	right = 0;
	unsigned short	up = 0;
	unsigned short	down = 0;
}					t_DirectionPolicy;

typedef struct			s_TileQueueItem
{
	t_Pos				pos;
	t_Direction			directionFrom;
	t_DirectionPolicy	policies;
	int					currentDistance;
	int					nbCurrentPathLength;
	std::vector<t_Pos>	currentPathTiles;
}						t_TileQueueItem;

bool isPositionValid(const int& _mapVerticalSize, const int& _mapHorizontalSize, const t_Pos& _pos);
bool doesPolicyBlockMove(const t_DirectionPolicy& _policies, const t_Direction& _targetDirection);
bool isPathTileAlreadyTaken(const std::vector<t_Pos>& _path, const t_Pos& _pos);

bool operator!=(const t_Pos& _p1, const t_Pos& _p2);
bool operator==(const t_Pos& _p1, const t_Pos& _p2);

//void moveOnNextTile(std::vector<std::string>& _map, std::vector<std::vector<int>>& _distances, t_DirectionPolicy& _policies, int _currentDistance);
void updatePolicies(t_DirectionPolicy& _policies, const t_Direction& _targetDirection);
int getDistanceToTargetTile(const std::vector<std::string>& _map, const t_Pos& _pos);

void displayDistances(const std::vector<std::vector<int>>& _distances);

void daySeventeen(const bool& isPartTwo = false);