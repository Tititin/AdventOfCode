#include "DaySix.h"

bool checkIfUnique(const t_Pos& _pos, const std::vector<t_Pos>& _visited)
{
	bool	isNotUnique = false;

	//std::cout << "CHECKING IF POS " << _pos.x << ";" << _pos.y << " IS UNIQUE" << std::endl;

	for (int i = 0; i < _visited.size() && !isNotUnique; i++)
	{
		if (_pos.x == _visited[i].x && _pos.y == _visited[i].y)
		{
			//std::cout << "Error with pos " << _pos.x << ";" << _pos.y << std::endl;
			//std::cout << "Position " << _visited[i].x << ";" << _visited[i].y << " already visited" << std::endl;
			isNotUnique = true;
		}
	}
	return !isNotUnique;
}

void moveOneTile(t_Pos& _pos, t_Direction& _direction, const std::vector<std::string>& _labMap)
{
	switch (_direction)
	{
	case UP:
		if (_pos.y - 1 < 0 || (_labMap[_pos.y - 1][_pos.x] != '#' && _labMap[_pos.y - 1][_pos.x] != 'O'))
			_pos.y -= 1;
		else
			_direction = RIGHT;
		break;

	case DOWN:
		if (_pos.y + 1 >= _labMap.size() || (_labMap[_pos.y + 1][_pos.x] != '#' && _labMap[_pos.y + 1][_pos.x] != 'O'))
			_pos.y += 1;
		else
			_direction = LEFT;
		break;

	case LEFT:
		if (_pos.x - 1 < 0 || (_labMap[_pos.y][_pos.x - 1] != '#' && _labMap[_pos.y][_pos.x - 1] != 'O'))
			_pos.x -= 1;
		else
			_direction = UP;
		break;

	case RIGHT:
		if (_pos.x + 1 >= _labMap[_pos.y].size() || (_labMap[_pos.y][_pos.x + 1] != '#' && _labMap[_pos.y][_pos.x + 1] != 'O'))
			_pos.x += 1;
		else
			_direction = DOWN;
		break;
	}
}

void daySix(const bool& isPartTwo)
{
	FileParser	_file("2024\\InputFiles\\inputD6.txt");
	std::string	line;
	unsigned long long int	finalValue = 0;

	std::vector<t_Pos>			uniquePositions;
	std::vector<std::string>	labMap;

	t_Pos						guardPos;
	t_Direction					guardDirection;

	t_Pos						loopTry = t_Pos{ 0, 0 };
	int							nbTry = 0;
	int							nbDuplicateTiles = 0;
	unsigned int				loopPossibilities = 0;

	while ((line = _file.readLineToString()) != "")
		labMap.push_back(line);

	bool	guardFound = false;

	for (int y = 0; y < labMap.size() && !guardFound; y++)
	{
		for (int x = 0; x < labMap[y].size() && !guardFound; x++)
		{
			if (labMap[y][x] == '^')
			{
				guardPos = t_Pos{ x, y };
				guardFound = true;
				guardDirection = UP;

				//std::cout << "FOUND GUARD AT POS " << x << ";" << y << std::endl;
			}
		}
	}

	if (!isPartTwo)
	{
		while (guardPos.x >= 0 && guardPos.x < labMap[0].size()
			&& guardPos.y >= 0 && guardPos.y < labMap.size())
		{
			//std::cout << "ANALYZING POS " << guardPos.x << ";" << guardPos.y << std::endl;
			if (checkIfUnique(guardPos, uniquePositions))
			{
				uniquePositions.push_back(guardPos);
				nbDuplicateTiles = 0;
			}
			else
				nbDuplicateTiles += 1;

			if (nbDuplicateTiles > labMap.size() * labMap[0].size())
			{
				loopPossibilities += 1;
				break;
			}

			moveOneTile(guardPos, guardDirection, labMap);
		}
	}

	finalValue = uniquePositions.size();
	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}