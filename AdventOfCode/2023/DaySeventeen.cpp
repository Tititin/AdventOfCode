#include "DaySeventeen.h"

bool isPositionValid(const int& _mapVerticalSize, const int& _mapHorizontalSize, const t_Pos& _pos)
{
	if (_pos.x < 0 || _pos.x >= _mapHorizontalSize)
		return false;
	if (_pos.y < 0 || _pos.y >= _mapVerticalSize)
		return false;
	return true;
}

bool doesPolicyBlockMove(const t_DirectionPolicy& _policies, const t_Direction& _targetDirection)
{
	bool blockMove = false;

	switch (_targetDirection)
	{
	case LEFT:
		blockMove = _policies.left == 3;
		break;
	case RIGHT:
		blockMove = _policies.right == 3;
		break;
	case UP:
		blockMove = _policies.up == 3;
		break;
	case DOWN:
		blockMove = _policies.down == 3;
		break;
	}

	return blockMove;
}

bool isPathTileAlreadyTaken(const std::vector<t_Pos>& _path, const t_Pos& _pos)
{
	for (int i = 0; i < _path.size(); i++)
		if (_pos == _path[i])
			return true;
	return false;
}

bool operator!=(const t_Pos& _p1, const t_Pos& _p2)
{
	if (_p1.x != _p2.x || _p1.y != _p2.y)
		return true;
	else
		return false;
}

bool operator==(const t_Pos& _p1, const t_Pos& _p2)
{
	if (_p1.x == _p2.x && _p1.y == _p2.y)
		return true;
	else
		return false;
}

void updatePolicies(t_DirectionPolicy& _policies, const t_Direction& _targetDirection)
{
	switch (_targetDirection)
	{
	case LEFT:
		_policies.left += 1;
		_policies.down = 0;
		_policies.right = 0;
		_policies.up = 0;
		break;
	case RIGHT:
		_policies.left = 0;
		_policies.down = 0;
		_policies.right += 1;
		_policies.up = 0;
		break;
	case UP:
		_policies.left = 0;
		_policies.down = 0;
		_policies.right = 0;
		_policies.up += 1;
		break;
	case DOWN:
		_policies.left = 0;
		_policies.down += 1;
		_policies.right = 0;
		_policies.up = 0;
		break;
	}
}

int getDistanceToTargetTile(const std::vector<std::string>& _map, const t_Pos& _pos)
{
	return (_map[_pos.y][_pos.x] - 48);
}

void displayDistances(const std::vector<std::vector<int>>& _distances)
{
	for (int i = 0; i < _distances[0].size() * 4 + 1; i++)
		std::cout << "-";
	std::cout << std::endl;

	for (int y = 0; y < _distances.size(); y++)
	{
		std::cout << "|";
		for (int x = 0; x < _distances[y].size(); x++)
		{
			std::cout << (_distances[y][x] / 100);
			std::cout << (_distances[y][x] % 100 / 10);
			std::cout << (_distances[y][x] % 10);
			std::cout << "|";
		}
		//std::cout << (_distances[y][x] + 48) % 10;
		std::cout << std::endl;
	}

	for (int i = 0; i < _distances[0].size() * 4 + 1; i++)
		std::cout << "-";
	std::cout << std::endl;
}

void daySeventeen(const bool& isPartTwo)
{
	FileParser	_fileParser("2023\\InputFiles\\inputD17bis.txt");
	std::string	line;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	std::vector<std::string>	map;
	std::vector<std::vector<int>>			distances;
	int							mapVerticalSize;
	int							mapHorizontalSize;

	t_Direction					direction;
	t_DirectionPolicy			policies;

	t_TileQueueItem				item;
	t_Pos						startPos = t_Pos{ 0, 0 };
	t_Pos						endPos;

	std::queue<t_TileQueueItem>	queue;

	int						runnerZeroDeviation = 0;

	unsigned long long int		finalValue = 0;

	// DEBUG
	FileParser	debugFile("2023\\InputFiles\\inputD17bis.txt");
	int	debugWord;
	//std::map<t_Pos, int>	debugMap;
	std::vector<t_Pos> debugCoor;
	std::vector<int> debugDist;
	t_Pos	debug;

	while ((line = _fileParser.readLineToString()) != "")
	{
		std::vector<int>	dist(line.size(), 0);

		map.push_back(line);
		distances.push_back(dist);
	}

	item.currentDistance = distances[startPos.y][startPos.x];
	item.directionFrom = NONE;
	item.policies = policies;
	item.pos = startPos;
	item.nbCurrentPathLength = 0;

	queue.push(item);

	mapVerticalSize = map.size();
	mapHorizontalSize = map[0].size();
	endPos = t_Pos{ mapHorizontalSize - 1, mapVerticalSize - 1 };

	map[0][0] = '0'; // GROSS

	// RUNNER ZERO
	while (distances[endPos.y][endPos.x] == 0)
	{
		while (item.pos.x != endPos.x)
		{
			distances[item.pos.y][item.pos.x] = item.currentDistance + map[item.pos.y][item.pos.x] - 48;
			item.currentDistance = distances[item.pos.y][item.pos.x];
			if (isPositionValid(mapVerticalSize, mapHorizontalSize, t_Pos{ item.pos.x + 1, item.pos.y }) && !doesPolicyBlockMove(item.policies, RIGHT))
			{
				item.directionFrom = LEFT;
				updatePolicies(item.policies, RIGHT);
				item.pos.x += 1;
				item.nbCurrentPathLength += 1;
			}
			else if (doesPolicyBlockMove(item.policies, RIGHT))
			{
				item.directionFrom = UP;
				updatePolicies(item.policies, DOWN);
				item.pos.y += 1;
				item.nbCurrentPathLength += 1;
			}
		}
		while (item.pos.y != endPos.y)
		{
			distances[item.pos.y][item.pos.x] = item.currentDistance + map[item.pos.y][item.pos.x] - 48;
			item.currentDistance = distances[item.pos.y][item.pos.x];
			if (isPositionValid(mapVerticalSize, mapHorizontalSize, t_Pos{ item.pos.x, item.pos.y + 1 }) && !doesPolicyBlockMove(item.policies, DOWN) && runnerZeroDeviation != 2)
			{
				item.directionFrom = UP;
				updatePolicies(item.policies, DOWN);
				item.pos.y += 1;
				item.nbCurrentPathLength += 1;
				if (runnerZeroDeviation == 1)
					runnerZeroDeviation = 2;
			}
			else if (doesPolicyBlockMove(item.policies, DOWN) && runnerZeroDeviation == 0)
			{
				item.directionFrom = RIGHT;
				updatePolicies(item.policies, LEFT);
				item.pos.x -= 1;
				item.nbCurrentPathLength += 1;
				runnerZeroDeviation = 1;
			}
			else
			{
				item.directionFrom = LEFT;
				updatePolicies(item.policies, RIGHT);
				item.pos.x += 1;
				item.nbCurrentPathLength += 1;
				runnerZeroDeviation = 0;
			}
		}
		distances[endPos.y][endPos.y] = item.currentDistance + map[endPos.y][endPos.x] - 48;
	}

	for (; !queue.empty(); queue.pop())
	{
		// DEBUG
		system("cls");
		std::cout << "==========DEBUG INFO==========" << std::endl;
		std::cout << "CURRENT ITEM POS		: ( " << queue.front().pos.x << ";" << queue.front().pos.y << " )" << std::endl;
		std::cout << "CURRENT ITEM DISTANCE : " << queue.front().currentDistance << std::endl;
		std::cout << "CURRENT ITEM POLICIES : " << queue.front().policies.left << "L " << queue.front().policies.down << "D " << queue.front().policies.right << "R "
			<< queue.front().policies.up << "U" << std::endl;
		std::cout << "CURRENT PATH LENGTH : " << queue.front().nbCurrentPathLength << " / " << mapHorizontalSize * mapVerticalSize << std::endl;
		std::cout << "QUEUE SIZE : " << queue.size() << std::endl;

		item = queue.front();

		// UPDATE DISTANCES
		if (item.pos != endPos || distances[item.pos.y][item.pos.x] > item.currentDistance + map[item.pos.y][item.pos.x] - 48)
			distances[item.pos.y][item.pos.x] = item.currentDistance + map[item.pos.y][item.pos.x] - 48;
		item.currentDistance = distances[item.pos.y][item.pos.x];
		item.currentPathTiles.push_back(item.pos);

		// ANALYZE NEXT TILES
			// Check #1 : Check if distance < endPoint current distance && not back at startPoint (pos == startPos && distance > 0)
			// Check #2 : Check if position is valid and authorized by current policies
			// Check #3 : Check if next tile is not 9
		if (item.currentDistance < distances[endPos.y][endPos.x]
			&& ((item.pos == startPos && item.currentDistance == 0) || item.pos != startPos))
		{
			if (isPositionValid(mapVerticalSize, mapHorizontalSize, t_Pos{ item.pos.x + 1, item.pos.y }) && !doesPolicyBlockMove(item.policies, RIGHT)
				&& item.directionFrom != RIGHT)
			{
				if (map[item.pos.y][item.pos.x + 1] != '9' && !isPathTileAlreadyTaken(item.currentPathTiles, t_Pos{item.pos.x + 1, item.pos.y}))
				{
					item.directionFrom = LEFT;
					updatePolicies(item.policies, RIGHT);
					item.pos.x += 1;
					item.nbCurrentPathLength += 1;
					queue.push(item);
				}
			}
			if (isPositionValid(mapVerticalSize, mapHorizontalSize, t_Pos{ item.pos.x, item.pos.y + 1 }) && !doesPolicyBlockMove(item.policies, DOWN)
				&& item.directionFrom != DOWN)
			{
				if (map[item.pos.y + 1][item.pos.x] != '9' && !isPathTileAlreadyTaken(item.currentPathTiles, t_Pos{ item.pos.x, item.pos.y + 1 }))
				{
					item.directionFrom = UP;
					updatePolicies(item.policies, DOWN);
					item.pos.y += 1;
					item.nbCurrentPathLength += 1;
					queue.push(item);
				}
			}
			if (isPositionValid(mapVerticalSize, mapHorizontalSize, t_Pos{ item.pos.x - 1, item.pos.y }) && !doesPolicyBlockMove(item.policies, LEFT)
				&& item.directionFrom != LEFT)
			{
				if (map[item.pos.y][item.pos.x - 1] != '9' && !isPathTileAlreadyTaken(item.currentPathTiles, t_Pos{ item.pos.x - 1, item.pos.y }))
				{
					item.directionFrom = RIGHT;
					updatePolicies(item.policies, LEFT);
					item.pos.x -= 1;
					item.nbCurrentPathLength += 1;
					queue.push(item);
				}
			}
			if (isPositionValid(mapVerticalSize, mapHorizontalSize, t_Pos{ item.pos.x, item.pos.y - 1 }) && !doesPolicyBlockMove(item.policies, UP)
				&& item.directionFrom != UP)
			{
				if (map[item.pos.y - 1][item.pos.x] != '9' && !isPathTileAlreadyTaken(item.currentPathTiles, t_Pos{ item.pos.x, item.pos.y - 1 }))
				{
					item.directionFrom = DOWN;
					updatePolicies(item.policies, UP);
					item.pos.x += 1;
					item.nbCurrentPathLength += 1;
					queue.push(item);
				}
			}
		}

		for (int i = 0; i < distances[0].size() * 4 + 1; i++)
			std::cout << "-";
		std::cout << std::endl;

		for (int y = 0; y < distances.size(); y++)
		{
			std::cout << "|";
			for (int x = 0; x < distances[y].size(); x++)
			{
				t_Pos debugPos = t_Pos{ x, y };
				if (x == queue.front().pos.x && y == queue.front().pos.y)
					SetConsoleTextAttribute(hConsole, 14);
				else
				{
					for (int i = 0; i < debugCoor.size(); i++)
					{
						if (!(debugCoor[i] != debugPos))
							SetConsoleTextAttribute(hConsole, 10);
					}
				}
				std::cout << (distances[y][x] / 100);
				std::cout << (distances[y][x] % 100 / 10);
				std::cout << (distances[y][x] % 10);
				SetConsoleTextAttribute(hConsole, 8);
				std::cout << "|";
			}
			std::cout << std::endl;
		}

		for (int i = 0; i < distances[0].size() * 4 + 1; i++)
			std::cout << "-";
		std::cout << std::endl;

	}

	finalValue = distances[endPos.y][endPos.x];

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}
