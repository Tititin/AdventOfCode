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

	unsigned long long int		finalValue = 0;

	// DEBUG
	FileParser	debugFile("2023\\InputFiles\\inputD17debug.txt");
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

	while ((debugWord = debugFile.readWordToInt()) != -1)
	{
		debug.x = (long long int)debugWord;
		debugWord = debugFile.readWordToInt();
		debug.y = (long long int)debugWord;
		debugWord = debugFile.readWordToInt();

		//std::pair<t_Pos, int>

		//debugMap.insert(std::make_pair(debug, debugWord));

		debugCoor.push_back(debug);
		debugDist.push_back(debugWord);
	}

	item.currentDistance = distances[startPos.y][startPos.x];
	item.directionFrom = NONE;
	item.policies = policies;
	item.pos = startPos;
	item.nbCurrentPathLength = 0;
	//item.currentPathTiles.push_back(startPos);

	queue.push(item);

	mapVerticalSize = map.size();
	mapHorizontalSize = map[0].size();
	//endPos = t_Pos{ 0, 0 };
	//startPos = t_Pos{ mapHorizontalSize - 1, mapVerticalSize - 1 };
	endPos = t_Pos{ mapHorizontalSize - 1, mapVerticalSize - 1 };

	//item.pos = startPos;
	//queue.push(item);

	map[0][0] = '0'; // GROSS

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

		/*if (queue.front().nbCurrentPathLength < mapHorizontalSize * mapVerticalSize
			&& (distances[queue.front().pos.y][queue.front().pos.x] == 0
			|| distances[endPos.y][endPos.x] == 0
			|| queue.front().currentDistance < distances[endPos.y][endPos.x]))*/
		if (distances[queue.front().pos.y][queue.front().pos.x] == 0
			|| queue.front().currentDistance + (map[queue.front().pos.y][queue.front().pos.x] - 48) < distances[queue.front().pos.y][queue.front().pos.x] + 1)
		{
			if (queue.front().pos == endPos
				&& (distances[endPos.y][endPos.x] == 0
					|| queue.front().currentDistance + map[endPos.y][endPos.x] - 48 < distances[endPos.y][endPos.x]))
				distances[queue.front().pos.y][queue.front().pos.x] = queue.front().currentDistance + (map[queue.front().pos.y][queue.front().pos.x] - 48);
			else if (queue.front().pos != endPos)
				distances[queue.front().pos.y][queue.front().pos.x] = queue.front().currentDistance + (map[queue.front().pos.y][queue.front().pos.x] - 48);
			item.currentDistance = distances[queue.front().pos.y][queue.front().pos.x];
			item.nbCurrentPathLength = queue.front().nbCurrentPathLength + 1;
			//item.currentPathTiles.push_back(queue.front().pos);
			//if (queue.front().pos != endPos)
			//{
			if (isPositionValid(mapVerticalSize, mapHorizontalSize, t_Pos{ queue.front().pos.x - 1, queue.front().pos.y }))
			{
				//if (queue.front().directionFrom != LEFT)
				if (!doesPolicyBlockMove(queue.front().policies, LEFT) && queue.front().directionFrom != LEFT)
				{
					//item.currentDistance = distances[queue.front().pos.y][queue.front().pos.x];
					item.policies = queue.front().policies;
					updatePolicies(item.policies, LEFT);
					item.pos.x = queue.front().pos.x - 1;
					item.pos.y = queue.front().pos.y;
					item.directionFrom = RIGHT;
					/*if (queue.front().pos != endPos && isPositionValid(mapVerticalSize, mapHorizontalSize, item.pos)
						&& (distances[item.pos.y][item.pos.x] > queue.front().currentDistance + (map[item.pos.y][item.pos.x] - 48)
							|| distances[item.pos.y][item.pos.x] == 0))
						queue.push(item);*/
						/* Si la position actuelle n'est pas celle de fin
						*  ET que la position suivante est valide
						*  ET que la case de fin n'ait pas encore été atteinte
						*		OU que la distance parcourue actuelle est inférieure à la distance la plus courte de la fin trouvée actuellement
						*
						* ALORS on ajoute la position suivante à la liste (si la distance est inférieure, peut-être que nous avons une chance d'atteindre la fin plus vite)
						* (si on tourne en rond, bah tôt ou tard on va dépasser la distance la plus courte de la fin, donc inutile de forcer)
						*/

					/*if (queue.front().pos != endPos && isPositionValid(mapVerticalSize, mapHorizontalSize, item.pos)
						&& !isPathTileAlreadyTaken(queue.front().currentPathTiles, item.pos))*/
					if (queue.front().pos != endPos && isPositionValid(mapVerticalSize, mapHorizontalSize, item.pos)
						&& (distances[endPos.y][endPos.x] == 0
							|| (distances[endPos.y][endPos.x] >= item.currentDistance)))
						queue.push(item);
				}
			}
			if (isPositionValid(mapVerticalSize, mapHorizontalSize, t_Pos{ queue.front().pos.x, queue.front().pos.y - 1 }))
			{
				//if (queue.front().directionFrom != UP)
				if (!doesPolicyBlockMove(queue.front().policies, UP) && queue.front().directionFrom != UP)
				{
					//item.currentDistance = distances[queue.front().pos.y][queue.front().pos.x];
					item.policies = queue.front().policies;
					updatePolicies(item.policies, UP);
					item.pos.x = queue.front().pos.x;
					item.pos.y = queue.front().pos.y - 1;
					item.directionFrom = DOWN;
					/*if (queue.front().pos != endPos && isPositionValid(mapVerticalSize, mapHorizontalSize, item.pos)
						&& (distances[item.pos.y][item.pos.x] > queue.front().currentDistance + (map[item.pos.y][item.pos.x] - 48)
							|| distances[item.pos.y][item.pos.x] == 0))
						queue.push(item);*/
					/*if (queue.front().pos != endPos && isPositionValid(mapVerticalSize, mapHorizontalSize, item.pos)
						&& !isPathTileAlreadyTaken(queue.front().currentPathTiles, item.pos))*/
					if (queue.front().pos != endPos && isPositionValid(mapVerticalSize, mapHorizontalSize, item.pos)
						&& (distances[endPos.y][endPos.x] == 0
							|| (distances[endPos.y][endPos.x] >= item.currentDistance)))
						queue.push(item);
				}
			}
			if (isPositionValid(mapVerticalSize, mapHorizontalSize, t_Pos{ queue.front().pos.x + 1, queue.front().pos.y }))
			{
				//if (queue.front().directionFrom != RIGHT)
				if (!doesPolicyBlockMove(queue.front().policies, RIGHT) && queue.front().directionFrom != RIGHT)
				{
					//item.currentDistance = distances[queue.front().pos.y][queue.front().pos.x];
					item.policies = queue.front().policies;
					updatePolicies(item.policies, RIGHT);
					item.pos.x = queue.front().pos.x + 1;
					item.pos.y = queue.front().pos.y;
					item.directionFrom = LEFT;
					/*if (queue.front().pos != endPos && isPositionValid(mapVerticalSize, mapHorizontalSize, item.pos)
						&& (distances[item.pos.y][item.pos.x] > queue.front().currentDistance + (map[item.pos.y][item.pos.x] - 48)
							|| distances[item.pos.y][item.pos.x] == 0))
						queue.push(item);*/
					/*if (queue.front().pos != endPos && isPositionValid(mapVerticalSize, mapHorizontalSize, item.pos)
						&& !isPathTileAlreadyTaken(queue.front().currentPathTiles, item.pos))*/
						if (queue.front().pos != endPos && isPositionValid(mapVerticalSize, mapHorizontalSize, item.pos)
						&& (distances[endPos.y][endPos.x] == 0
							|| (distances[endPos.y][endPos.x] >= item.currentDistance)))
						queue.push(item);
				}
			}
			if (isPositionValid(mapVerticalSize, mapHorizontalSize, t_Pos{ queue.front().pos.x, queue.front().pos.y + 1 }))
			{
				//if (queue.front().directionFrom != DOWN)
				if (!doesPolicyBlockMove(queue.front().policies, DOWN) && queue.front().directionFrom != DOWN)
				{
					//item.currentDistance = distances[queue.front().pos.y][queue.front().pos.x];
					item.policies = queue.front().policies;
					updatePolicies(item.policies, DOWN);
					item.pos.x = queue.front().pos.x;
					item.pos.y = queue.front().pos.y + 1;
					item.directionFrom = UP;
					/*if (queue.front().pos != endPos && isPositionValid(mapVerticalSize, mapHorizontalSize, item.pos)
						&& (distances[item.pos.y][item.pos.x] > queue.front().currentDistance + (map[item.pos.y][item.pos.x] - 48)
							|| distances[item.pos.y][item.pos.x] == 0))
						queue.push(item);*/
					/*if (queue.front().pos != endPos && isPositionValid(mapVerticalSize, mapHorizontalSize, item.pos)
						&& !isPathTileAlreadyTaken(queue.front().currentPathTiles, item.pos))*/
						if (queue.front().pos != endPos && isPositionValid(mapVerticalSize, mapHorizontalSize, item.pos)
						&& (distances[endPos.y][endPos.x] == 0
							|| (distances[endPos.y][endPos.x] >= item.currentDistance)))
						queue.push(item);
				}
			}
			//}
		}
		//displayDistances(distances);

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
				/*else if (debugMap.find(debugPos) != debugMap.end())
					SetConsoleTextAttribute(hConsole, 10);*/
				std::cout << (distances[y][x] / 100);
				std::cout << (distances[y][x] % 100 / 10);
				std::cout << (distances[y][x] % 10);
				SetConsoleTextAttribute(hConsole, 8);
				std::cout << "|";
			}
			//std::cout << (_distances[y][x] + 48) % 10;
			std::cout << std::endl;
		}

		for (int i = 0; i < distances[0].size() * 4 + 1; i++)
			std::cout << "-";
		std::cout << std::endl;

		//Sleep(5000);
	}


	/*for (int y = 0; y < distances.size(); y++)
	{
		for (int x = 0; x < distances[y].size(); x++)
			std::cout << (distances[y][x] + 48) % 10;
		std::cout << std::endl;
	}*/
	finalValue = distances[endPos.y][endPos.x];
	//finalValue = item.currentDistance;

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}
