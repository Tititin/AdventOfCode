#include "DayThree.h"

bool isHouseAlreadyVisited(const std::vector<t_Pos>& houses, const t_Pos& pos)
{
	for (int i = 0; i < houses.size(); i++)
	{
		if (houses[i].x == pos.x && houses[i].y == pos.y)
			return true;
	}
	return false;
}

void dayThree(const bool& isPartTwo)
{
	FileParser		_file("2015\\InputFiles\\inputD3.txt");
	std::string		line;
	unsigned long long int	finalValue = 0;

	t_Pos			currentPos = t_Pos{ 0, 0 };
	t_Pos			robotPos = t_Pos{ 0, 0 };
	std::vector<t_Pos>	visitedHouses;

	line = _file.readLineToString();
	visitedHouses.push_back(currentPos);

	for (int i = 0; i < line.size(); i++)
	{
		switch (line[i])
		{
		case '>':
			if (i % 2 == 0 || !isPartTwo)
				currentPos.x += 1;
			else
				robotPos.x += 1;
			break;
		case '<':
			if (i % 2 == 0 || !isPartTwo)
				currentPos.x -= 1;
			else
				robotPos.x -= 1;
			break;
		case 'v':
			if (i % 2 == 0 || !isPartTwo)
				currentPos.y += 1;
			else
				robotPos.y += 1;
			break;
		case '^':
			if (i % 2 == 0 || !isPartTwo)
				currentPos.y -= 1;
			else
				robotPos.y -= 1;
			break;
		}

		if (!isHouseAlreadyVisited(visitedHouses, currentPos))
			visitedHouses.push_back(currentPos);
		if (!isHouseAlreadyVisited(visitedHouses, robotPos))
			visitedHouses.push_back(robotPos);
	}

	std::cout << "FINAL VALUE = " << visitedHouses.size();
}