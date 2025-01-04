#include "DayFourteen.h"

unsigned long long int getRobotsInQuadrant(const std::vector<t_Pos>& _robots, const t_Pos& _northWest, const t_Pos& _southEast)
{
	unsigned long long int	result = 0;

	for (int y = _northWest.y; y <= _southEast.y; y++)
	{
		for (int x = _northWest.x; x <= _southEast.x; x++)
		{
			for (int i = 0; i < _robots.size(); i++)
			{
				if (_robots[i].x == x && _robots[i].y == y)
					result += 1;
			}
		}
	}
	return result;
}

void updateMap(std::vector<std::string>& _map, std::vector<t_Pos>& _robots)
{
	for (int i = 0; i < _map.size(); i++)
		_map[i] = std::string(101, '.');

	for (int y = 0; y < _map.size(); y++)
	{
		for (int x = 0; x < _map[y].size(); x++)
		{
			for (int i = 0; i < _robots.size(); i++)
			{
				if (_robots[i].x == x && _robots[i].y == y)
					_map[y][x] = '*';
			}
		}
	}
}

void dayFourteen(const bool& isPartTwo)
{
	FileParser	_file("2024\\InputFiles\\inputD14.txt");
	std::string	word;
	unsigned long long int	finalValue = 1;

	std::vector<t_Pos>	robotPos;
	std::vector<t_Pos>	robotVelocities;

	std::vector<std::string>	robotMap(103, std::string(101, '.'));

	while ((word = _file.readWordToString()) != "")
	{
		t_Pos		tmp;
		int			commaPos = 0;
		bool		isNegativeNumber = false;

		for (int i = 2; word[i] != ','; i++)
		{
			if (word[i] == '-')
				isNegativeNumber = true;
			else
				tmp.x = tmp.x * 10 + (word[i] - '0');

			if (word[i + 1] == ',')
				commaPos = i + 1;
		}
		if (isNegativeNumber)
			tmp.x *= -1;
		isNegativeNumber = false;
		for (int i = commaPos + 1; i < word.size(); i++)
		{
			if (word[i] == '-')
				isNegativeNumber = true;
			else
				tmp.y = tmp.y * 10 + (word[i] - '0');
		}
		if (isNegativeNumber)
			tmp.y *= -1;

		if (word[0] == 'p')
			robotPos.push_back(tmp);
		else if (word[0] == 'v')
			robotVelocities.push_back(tmp);

		tmp.x = 0;
		tmp.y = 0;
	}

	for (int s = 0; s < 100 || isPartTwo; s++)
	{
		for (int i = 0; i < robotPos.size(); i++)
		{
			robotPos[i].x += robotVelocities[i].x;
			robotPos[i].y += robotVelocities[i].y;

			if (robotPos[i].x < 0)
				robotPos[i].x += 101;
			else if (robotPos[i].x >= 101)
				robotPos[i].x = robotPos[i].x % 101;

			if (robotPos[i].y < 0)
				robotPos[i].y += 103;
			else if (robotPos[i].y >= 103)
				robotPos[i].y = robotPos[i].y % 103;
		}
		if (isPartTwo)
		{
			updateMap(robotMap, robotPos);
			if (s % 103 == 41) // 41 is the first number where the display had some kind of pattern. "Cycling" every 103 steps.
			{
				system("cls");
				for (int i = 0; i < robotMap.size(); i++)
					std::cout << robotMap[i] << std::endl;
				std::cout << "ELAPSED SECONDS = " << s << std::endl;
				//system("pause");
			}
			//Sleep(1200);
		}
	}

	finalValue *= getRobotsInQuadrant(robotPos, t_Pos{ 0, 0 }, t_Pos{ 49, 50 });
	finalValue *= getRobotsInQuadrant(robotPos, t_Pos{ 51, 0 }, t_Pos{ 100, 50 });
	finalValue *= getRobotsInQuadrant(robotPos, t_Pos{ 0, 52 }, t_Pos{ 49, 102 });
	finalValue *= getRobotsInQuadrant(robotPos, t_Pos{ 51, 52 }, t_Pos{ 100, 102 });

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}
