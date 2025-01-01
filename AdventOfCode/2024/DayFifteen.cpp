#include "DayFifteen.h"

bool pushBoxes(std::vector<std::string>& _boxesMap, const t_Pos& _robotPos, const t_Direction& _direction)
{
	int x;
	int y;

	bool isPushed = false;

	switch (_direction)
	{
	case RIGHT:
		x = _robotPos.x + 1;

		while (_boxesMap[_robotPos.y][x] == 'O')
			x += 1;
		if (_boxesMap[_robotPos.y][x] == '.')
		{
			_boxesMap[_robotPos.y][x] = 'O';
			_boxesMap[_robotPos.y][_robotPos.x + 1] = '.';
			isPushed = true;
		}
		break;

	case LEFT:
		x = _robotPos.x - 1;

		while (_boxesMap[_robotPos.y][x] == 'O')
			x -= 1;
		if (_boxesMap[_robotPos.y][x] == '.')
		{
			_boxesMap[_robotPos.y][x] = 'O';
			_boxesMap[_robotPos.y][_robotPos.x - 1] = '.';
			isPushed = true;
		}
		break;

	case UP:
		y = _robotPos.y - 1;

		while (_boxesMap[y][_robotPos.x] == 'O')
			y -= 1;
		if (_boxesMap[y][_robotPos.x] == '.')
		{
			_boxesMap[y][_robotPos.x] = 'O';
			_boxesMap[_robotPos.y - 1][_robotPos.x] = '.';
			isPushed = true;
		}
		break;

	case DOWN:
		y = _robotPos.y + 1;

		while (_boxesMap[y][_robotPos.x] == 'O')
			y += 1;
		if (_boxesMap[y][_robotPos.x] == '.')
		{
			_boxesMap[y][_robotPos.x] = 'O';
			_boxesMap[_robotPos.y + 1][_robotPos.x] = '.';
			isPushed = true;
		}
		break;
	}

	return (isPushed);
}

void dayFifteen(const bool& isPartTwo)
{
	FileParser	_file("2024\\InputFiles\\inputD15.txt");
	std::string	line;
	unsigned long long int	finalValue = 0;

	t_Pos	robotPos = t_Pos{ 0, 0 };

	std::vector<std::string>	boxesMap;

	while ((line = _file.readLineToString()) != "")
	{
		boxesMap.push_back(line);
		for (int i = 0; i < line.size(); i++)
			if (line[i] == '@')
				robotPos.x = i;
		if (robotPos.x == 0)
			robotPos.y += 1;
	}

	/*std::cout << "INITIAL STATE" << std::endl;
	for (int i = 0; i < boxesMap.size(); i++)
		std::cout << boxesMap[i] << std::endl;
	std::cout << std::endl;*/

	while ((line = _file.readLineToString()) != "") // TODO : Move obstacles
	{
		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] == '>' && boxesMap[robotPos.y][robotPos.x + 1] == '.')
			{
				boxesMap[robotPos.y][robotPos.x] = '.';
				robotPos.x += 1;
				boxesMap[robotPos.y][robotPos.x] = '@';
			}
			else if (line[i] == '>' && boxesMap[robotPos.y][robotPos.x + 1] == 'O')
			{
				if (pushBoxes(boxesMap, robotPos, RIGHT))
				{
					boxesMap[robotPos.y][robotPos.x] = '.';
					robotPos.x += 1;
					boxesMap[robotPos.y][robotPos.x] = '@';
				}
			}

			if (line[i] == '<' && boxesMap[robotPos.y][robotPos.x - 1] == '.')
			{
				boxesMap[robotPos.y][robotPos.x] = '.';
				robotPos.x -= 1;
				boxesMap[robotPos.y][robotPos.x] = '@';
			}
			else if (line[i] == '<' && boxesMap[robotPos.y][robotPos.x - 1] == 'O')
			{
				if (pushBoxes(boxesMap, robotPos, LEFT))
				{
					boxesMap[robotPos.y][robotPos.x] = '.';
					robotPos.x -= 1;
					boxesMap[robotPos.y][robotPos.x] = '@';
				}
			}

			if (line[i] == '^' && boxesMap[robotPos.y - 1][robotPos.x] == '.')
			{
				boxesMap[robotPos.y][robotPos.x] = '.';
				robotPos.y -= 1;
				boxesMap[robotPos.y][robotPos.x] = '@';
			}
			else if (line[i] == '^' && boxesMap[robotPos.y - 1][robotPos.x] == 'O')
			{
				if (pushBoxes(boxesMap, robotPos, UP))
				{
					boxesMap[robotPos.y][robotPos.x] = '.';
					robotPos.y -= 1;
					boxesMap[robotPos.y][robotPos.x] = '@';
				}
			}

			if (line[i] == 'v' && boxesMap[robotPos.y + 1][robotPos.x] == '.')
			{
				boxesMap[robotPos.y][robotPos.x] = '.';
				robotPos.y += 1;
				boxesMap[robotPos.y][robotPos.x] = '@';
			}
			else if (line[i] == 'v' && boxesMap[robotPos.y + 1][robotPos.x] == 'O')
			{
				if (pushBoxes(boxesMap, robotPos, DOWN))
				{
					boxesMap[robotPos.y][robotPos.x] = '.';
					robotPos.y += 1;
					boxesMap[robotPos.y][robotPos.x] = '@';
				}
			}

			/*std::cout << "MOVE " << i + 1 << std::endl;
			for (int i = 0; i < boxesMap.size(); i++)
				std::cout << boxesMap[i] << std::endl;
			std::cout << std::endl;*/
		}
	}

	for (int y = 1; y < boxesMap.size() - 1; y++)
	{
		for (int x = 1; x < boxesMap[y].size() - 1; x++)
			if (boxesMap[y][x] == 'O')
				finalValue += y * 100 + x;
	}

	for (int i = 0; i < boxesMap.size(); i++)
		std::cout << boxesMap[i] << std::endl;
	std::cout << std::endl;

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}
