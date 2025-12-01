#include "DayTwentyThree.h"

bool	checkValidTile(const int& _mapHeight, const int& _mapWidth, const t_Pos& _pos)
{
	if (_pos.x < 0
		|| _pos.y < 0
		|| _pos.x >= _mapWidth
		|| _pos.y >= _mapHeight)
		return false;
	return true;
}

bool checkAlreadyTakenPath(const std::vector<t_Pos>& _tiles, const t_Pos& _pos)
{
	bool	isNewTile = true;
	for (int i = 0; i < _tiles.size() && isNewTile; i++)
		if (_tiles[i] == _pos)
			isNewTile = false;
	return isNewTile;
}

void	dayTwentyThree(const bool& isPartTwo)
{
	FileParser	_fileParser("2023\\InputFiles\\inputD23.txt");
	std::string	line;

	unsigned long long int	finalValue = 0;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	std::vector<std::string>	map;
	std::vector<std::vector<int>>			distances;
	std::map<t_Pos, t_Pos>		crossPathsLinks;
	int							mapVerticalSize;
	int							mapHorizontalSize;

	t_Direction					direction;

	t_CrossPathTileQueueItem	item;
	t_Pos						startPos = t_Pos{ 1, 0 };
	t_Pos						endPos;

	std::queue<t_CrossPathTileQueueItem>	crossPathQueue;
	std::queue<t_CrossPathTileQueueItem>	queue;

	bool						firstCrossPathsFound = false;
	int							crossLocks = 0;

	while ((line = _fileParser.readLineToString()) != "")
	{
		std::vector<int>	dist;

		map.push_back(line);

		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] == '#')
				dist.push_back(-2);
			else
				dist.push_back(0);
		}

		distances.push_back(dist);
	}

	if (isPartTwo)
	{
		// CROSSPATHS LINKS REGISTRATION
		item.pos = startPos;
		item.currentDistance = 0;
		item.nbCurrentPathLength = 1;
		item.currentPathTiles.push_back(startPos);

		crossPathQueue.push(item);
		endPos = t_Pos{ (long long)map[0].size() - 2, (long long)map.size() - 1 };

		for (; !crossPathQueue.empty(); crossPathQueue.pop())
		{
			if (queue.front().pos != endPos)
			{
				t_Pos	upTile = t_Pos{ queue.front().pos.x, queue.front().pos.y - 1 };
				t_Pos	rightTile = t_Pos{ queue.front().pos.x + 1, queue.front().pos.y };
				t_Pos	downTile = t_Pos{ queue.front().pos.x, queue.front().pos.y + 1 };
				t_Pos	leftTile = t_Pos{ queue.front().pos.x - 1, queue.front().pos.y };

				item.currentPathTiles = queue.front().currentPathTiles;

				if (checkValidTile(map.size(), map[0].size(), upTile) && checkAlreadyTakenPath(queue.front().currentPathTiles, upTile))
				{
					if (map[upTile.y][upTile.x] == '.' || (isPartTwo && map[upTile.y][upTile.x] != '#'))
					{
						item.pos = upTile;
						item.currentDistance = queue.front().currentDistance + 1;
						item.nbCurrentPathLength = queue.front().nbCurrentPathLength + 1;
						item.currentPathTiles.push_back(upTile);
						queue.push(item);
					}
				}
				if (checkValidTile(map.size(), map[0].size(), rightTile) && checkAlreadyTakenPath(queue.front().currentPathTiles, rightTile))
				{
					if (map[rightTile.y][rightTile.x] == '.' || map[rightTile.y][rightTile.x] == '>' || (isPartTwo && map[rightTile.y][rightTile.x] != '#'))
					{
						item.pos = rightTile;
						item.currentDistance = queue.front().currentDistance + 1;
						item.nbCurrentPathLength = queue.front().nbCurrentPathLength + 1;
						item.currentPathTiles.push_back(rightTile);
						queue.push(item);
					}
				}
				if (checkValidTile(map.size(), map[0].size(), downTile) && checkAlreadyTakenPath(queue.front().currentPathTiles, downTile))
				{
					if (map[downTile.y][downTile.x] == '.' || map[downTile.y][downTile.x] == 'v' || (isPartTwo && map[downTile.y][downTile.x] != '#'))
					{
						item.pos = downTile;
						item.currentDistance = queue.front().currentDistance + 1;
						item.nbCurrentPathLength = queue.front().nbCurrentPathLength + 1;
						item.currentPathTiles.push_back(downTile);
						queue.push(item);
					}
				}
				if (checkValidTile(map.size(), map[0].size(), leftTile) && checkAlreadyTakenPath(queue.front().currentPathTiles, leftTile))
				{
					if (map[leftTile.y][leftTile.x] == '.' || (isPartTwo && map[leftTile.y][leftTile.x] != '#'))
					{
						item.pos = leftTile;
						item.currentDistance = queue.front().currentDistance + 1;
						item.nbCurrentPathLength = queue.front().nbCurrentPathLength + 1;
						item.currentPathTiles.push_back(leftTile);
						queue.push(item);
					}
				}
			}
		}
	}

	// RUNNERS
	item.pos = startPos;
	item.currentDistance = 0;
	item.nbCurrentPathLength = 1;
	item.currentPathTiles.push_back(startPos);

	queue.push(item);

	for (; !queue.empty(); queue.pop())
	{
		//// DEBUG
		//system("cls");
		//std::cout << "==========DEBUG INFO==========" << std::endl;
		//std::cout << "CURRENT ITEM POS		: ( " << queue.front().pos.x << ";" << queue.front().pos.y << " )" << std::endl;
		//std::cout << "CURRENT ITEM DISTANCE : " << queue.front().currentDistance << std::endl;
		//std::cout << "CURRENT PATH LENGTH : " << queue.front().nbCurrentPathLength << std::endl;
		//std::cout << "QUEUE SIZE : " << queue.size() << std::endl;

		//std::cout << std::endl;

		//for (int y = 0; y < map.size(); y++)
		//{
		//	for (int x = 0; x < map[y].size(); x++)
		//	{
		//		if (map[y][x] == '#')
		//			SetConsoleTextAttribute(hConsole, 5);
		//		else if (t_Pos{ x, y } == queue.front().pos)
		//			SetConsoleTextAttribute(hConsole, 14);
		//		std::cout << map[y][x];

		//		SetConsoleTextAttribute(hConsole, 8);
		//	}
		//	std::cout << std::endl;
		//}
		//std::cout << std::endl;

		if (distances[queue.front().pos.y][queue.front().pos.x] < queue.front().currentDistance || queue.front().pos == startPos)
		{
			distances[queue.front().pos.y][queue.front().pos.x] = queue.front().currentDistance;
		}
		if (queue.front().pos != endPos)
		{
			t_Pos	upTile = t_Pos{ queue.front().pos.x, queue.front().pos.y - 1 };
			t_Pos	rightTile = t_Pos{ queue.front().pos.x + 1, queue.front().pos.y };
			t_Pos	downTile = t_Pos{ queue.front().pos.x, queue.front().pos.y + 1 };
			t_Pos	leftTile = t_Pos{ queue.front().pos.x - 1, queue.front().pos.y };

			item.currentPathTiles = queue.front().currentPathTiles;

			/*if (map[queue.front().pos.y][queue.front().pos.x] != '#' && map[queue.front().pos.y][queue.front().pos.x] != '.'
				&& !firstCrossPathsFound)*/
			if (map[queue.front().pos.y][queue.front().pos.x] != '#' && map[queue.front().pos.y][queue.front().pos.x] != '.')
			{
				//firstCrossPathsFound = true;
				if (crossLocks < 5)
				{
					crossLocks += 1;
					map[queue.front().pos.y][queue.front().pos.x] = '#';
				}
			}

			if (checkValidTile(map.size(), map[0].size(), upTile) && checkAlreadyTakenPath(queue.front().currentPathTiles, upTile))
			{
				if (map[upTile.y][upTile.x] == '.' || (isPartTwo && map[upTile.y][upTile.x] != '#'))
				{
					item.pos = upTile;
					item.currentDistance = queue.front().currentDistance + 1;
					item.nbCurrentPathLength = queue.front().nbCurrentPathLength + 1;
					item.currentPathTiles.push_back(upTile);
					queue.push(item);
				}
			}
			if (checkValidTile(map.size(), map[0].size(), rightTile) && checkAlreadyTakenPath(queue.front().currentPathTiles, rightTile))
			{
				if (map[rightTile.y][rightTile.x] == '.' || map[rightTile.y][rightTile.x] == '>' || (isPartTwo && map[rightTile.y][rightTile.x] != '#'))
				{
					item.pos = rightTile;
					item.currentDistance = queue.front().currentDistance + 1;
					item.nbCurrentPathLength = queue.front().nbCurrentPathLength + 1;
					item.currentPathTiles.push_back(rightTile);
					queue.push(item);
				}
			}
			if (checkValidTile(map.size(), map[0].size(), downTile) && checkAlreadyTakenPath(queue.front().currentPathTiles, downTile))
			{
				if (map[downTile.y][downTile.x] == '.' || map[downTile.y][downTile.x] == 'v' || (isPartTwo && map[downTile.y][downTile.x] != '#'))
				{
					item.pos = downTile;
					item.currentDistance = queue.front().currentDistance + 1;
					item.nbCurrentPathLength = queue.front().nbCurrentPathLength + 1;
					item.currentPathTiles.push_back(downTile);
					queue.push(item);
				}
			}
			if (checkValidTile(map.size(), map[0].size(), leftTile) && checkAlreadyTakenPath(queue.front().currentPathTiles, leftTile))
			{
				if (map[leftTile.y][leftTile.x] == '.' || (isPartTwo && map[leftTile.y][leftTile.x] != '#'))
				{
					item.pos = leftTile;
					item.currentDistance = queue.front().currentDistance + 1;
					item.nbCurrentPathLength = queue.front().nbCurrentPathLength + 1;
					item.currentPathTiles.push_back(leftTile);
					queue.push(item);
				}
			}
		}
		else
			finalValue = distances[endPos.y][endPos.x];
		//}
	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}