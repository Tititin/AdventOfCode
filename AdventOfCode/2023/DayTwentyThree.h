#pragma once

#include "FileParser.h"
#include "DaySeventeen.h"

typedef struct						s_CrossPath
{
	t_Pos							entryPoint;
	t_Pos							middlePoint;
	std::map<t_Direction, t_Pos>	exitPoints;
}									t_CrossPath;

typedef struct	s_CrossPathTileQueueItem : public t_TileQueueItem
{
	/* Let's try to work with pairs. The idea is :
	*	1. The runner enters in a crosspath and capture the position
	*	2. The runner chooses one output and register its position
	*	3. The runner runs the maze until it enters in a next crosspath and captures this position
	*	4. The runner go to the origin of this next crosspath and captures the position
	*	5. Once the four positions have been captured, double registration to create the double link in the map
	*	6. Dest crossPath become new origin crosspath
	*	7. Repeat from step 2
	*/

	t_CrossPath	origin;
	t_CrossPath	dest;
	t_Pos		exitPointFrom = t_Pos{ -1, -1 };
	bool		isOnCrossPath = false;
	std::vector<t_Pos>	takenCrossPaths;
}				t_CrossPathTileQueueItem;

bool	checkValidTile(const int& _mapHeight, const int& _mapWidth, const t_Pos& _pos);
bool	checkAlreadyTakenPath(const std::vector<t_Pos>& _tiles, const t_Pos& _pos);

void	dayTwentyThree(const bool& isPartTwo = false);
