#include "DaySixteen.h"

bool checkIfDirectionIsHorizontal(const t_Direction& _direction)
{
	return (_direction == RIGHT || _direction == LEFT);
}

void turnRight(t_Direction& _direction)
{
	switch (_direction)
	{
	case LEFT:
		_direction = UP;
		break;
	case UP:
		_direction = RIGHT;
		break;
	case RIGHT:
		_direction = DOWN;
		break;
	case DOWN:
		_direction = LEFT;
		break;
	}
}

void turnLeft(t_Direction& _direction)
{
	switch (_direction)
	{
	case LEFT:
		_direction = DOWN;
		break;
	case UP:
		_direction = LEFT;
		break;
	case RIGHT:
		_direction = UP;
		break;
	case DOWN:
		_direction = RIGHT;
		break;
	}
}

bool isDividerNotUsed(const std::vector<t_Pos>& _usedDividers, const t_Pos& _pos)
{
	for (int i = 0; i < _usedDividers.size(); i++)
	{
		if (_usedDividers[i].y == _pos.y && _usedDividers[i].x == _pos.x)
			return false;
	}
	return true;
}

bool checkAtLeastOneLaserIsRunning(const std::vector<bool>& _laserRunning)
{
	for (int i = 0; i < _laserRunning.size(); i++)
	{
		if (_laserRunning[i])
			return true;
	}
	return false;
}

void daySixteen(const bool& isPartTwo)
{
	FileParser					_fileParser("2023\\InputFiles\\inputD16.txt");
	std::string					line;

	t_Pos						pos = t_Pos{ 0, 0 };
	std::vector<t_Pos>			laserPos;
	std::vector<t_Direction>	laserDirections;
	std::vector<bool>			laserRunning;

	std::vector<t_Pos>			usedDividers;

	std::vector<std::string>	laserMap;
	std::vector<std::string>	energizedMap;

	unsigned int				finalValue = 0;

	while ((line = _fileParser.readLineToString()) != "")
	{
		laserMap.push_back(line);
		energizedMap.push_back(line);
	}

	laserPos.push_back(pos);
	laserDirections.push_back(RIGHT);
	laserRunning.push_back(true);

	while (checkAtLeastOneLaserIsRunning(laserRunning))
	{
		for (int i = 0; i < laserPos.size(); i++)
		{
			if (laserRunning[i])
			{
				if (energizedMap[laserPos[i].y][laserPos[i].x] != '#')
				{
					energizedMap[laserPos[i].y][laserPos[i].x] = '#';
					finalValue += 1;
				}

				if (laserMap[laserPos[i].y][laserPos[i].x] == '\\')
				{
					if (checkIfDirectionIsHorizontal(laserDirections[i]))
						turnRight(laserDirections[i]);
					else
						turnLeft(laserDirections[i]);
				}
				else if (laserMap[laserPos[i].y][laserPos[i].x] == '/')
				{
					if (checkIfDirectionIsHorizontal(laserDirections[i]))
						turnLeft(laserDirections[i]);
					else
						turnRight(laserDirections[i]);
				}
				else if (laserMap[laserPos[i].y][laserPos[i].x] == '|')
				{
					if (checkIfDirectionIsHorizontal(laserDirections[i]) && isDividerNotUsed(usedDividers, laserPos[i]))
					{
						laserPos.push_back(t_Pos{ laserPos[i].x, laserPos[i].y });
						if (laserDirections[i] == RIGHT)
							laserDirections.push_back(DOWN);
						else
							laserDirections.push_back(UP);
						turnLeft(laserDirections[i]);
						laserRunning.push_back(true);
						usedDividers.push_back(laserPos[i]);
					}
					else if (checkIfDirectionIsHorizontal(laserDirections[i]))
						laserRunning[i] = false;
				}
				else if (laserMap[laserPos[i].y][laserPos[i].x] == '-')
				{
					if (!checkIfDirectionIsHorizontal(laserDirections[i]) && isDividerNotUsed(usedDividers, laserPos[i]))
					{
						laserPos.push_back(t_Pos{ laserPos[i].x, laserPos[i].y });
						if (laserDirections[i] == DOWN)
							laserDirections.push_back(LEFT);
						else
							laserDirections.push_back(RIGHT);
						turnLeft(laserDirections[i]);
						laserRunning.push_back(true);
						usedDividers.push_back(laserPos[i]);
					}
					else if (!checkIfDirectionIsHorizontal(laserDirections[i]))
						laserRunning[i] = false;
				}

				switch (laserDirections[i])
				{
				case LEFT:
					laserPos[i].x -= 1;
					break;
				case RIGHT:
					laserPos[i].x += 1;
					break;
				case UP:
					laserPos[i].y -= 1;
					break;
				case DOWN:
					laserPos[i].y += 1;
					break;
				}

				if (laserPos[i].x < 0 || laserPos[i].x >= laserMap[0].size()
					|| laserPos[i].y < 0 || laserPos[i].y >= laserMap.size())
					laserRunning[i] = false;
			}
		}
	}

	for (int y = 0; y < energizedMap.size(); y++)
	{
		for (int x = 0; x < energizedMap[y].size(); x++)
		{
			if (energizedMap[y][x] == '#')
				std::cout << "#";
			else
				std::cout << ".";
		}
		std::cout << std::endl;
	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}
