#include "DayEighteen.h"

void dayEighteen(const bool& isPartTwo)
{
	FileParser	_file("2024\\InputFiles\\inputD18.txt");
	std::string	line;
	unsigned long long int	finalValue = 0;

	std::vector<std::vector<char>>	map(71, std::vector<char>(71, '.'));
	t_Pos							obstaclePos = t_Pos{ 0, 0 };
	int								limit = 0;

	std::vector<std::vector<int>>	pathfindingMap(71, std::vector<int>(71, 0));
	std::vector<t_Pos>				pathTile;

	while ((line = _file.readLineToString()) != "" && limit < 1024)
	{
		for (int i = 0; line[i] != ','; i++)
			obstaclePos.x = obstaclePos.x * 10 + (line[i] - '0');

		for (int i = line.find(',') + 1; i < line.size(); i++)
			obstaclePos.y = obstaclePos.y * 10 + (line[i] - '0');

		map[obstaclePos.y][obstaclePos.x] = '#';
		obstaclePos = t_Pos{ 0, 0 };
		limit += 1;
	}

	pathTile.push_back(t_Pos{ 0, 0 });

	for (int i = 0; i < pathTile.size(); i++)
	{
		t_Pos	currentPos = pathTile[i];

		if (currentPos.y - 1 >= 0 && map[currentPos.y - 1][currentPos.x] != '#')
		{
			if (pathfindingMap[currentPos.y - 1][currentPos.x] == 0 || pathfindingMap[currentPos.y][currentPos.x] + 1 < pathfindingMap[currentPos.y - 1][currentPos.x])
			{
				pathfindingMap[currentPos.y - 1][currentPos.x] = pathfindingMap[currentPos.y][currentPos.x] + 1;
				pathTile.push_back(t_Pos{ currentPos.x, currentPos.y - 1 });
			}
		}
		if (currentPos.x + 1 < 71 && map[currentPos.y][currentPos.x + 1] != '#')
		{
			if (pathfindingMap[currentPos.y][currentPos.x + 1] == 0 || pathfindingMap[currentPos.y][currentPos.x] + 1 < pathfindingMap[currentPos.y][currentPos.x + 1])
			{
				pathfindingMap[currentPos.y][currentPos.x + 1] = pathfindingMap[currentPos.y][currentPos.x] + 1;
				pathTile.push_back(t_Pos{ currentPos.x + 1, currentPos.y });
			}
		}
		if (currentPos.x - 1 >= 0 && map[currentPos.y][currentPos.x - 1] != '#')
		{
			if (pathfindingMap[currentPos.y][currentPos.x - 1] == 0 || pathfindingMap[currentPos.y][currentPos.x] + 1 < pathfindingMap[currentPos.y][currentPos.x - 1])
			{
				pathfindingMap[currentPos.y][currentPos.x - 1] = pathfindingMap[currentPos.y][currentPos.x] + 1;
				pathTile.push_back(t_Pos{ currentPos.x - 1, currentPos.y });
			}
		}
		if (currentPos.y + 1 < 71 && map[currentPos.y + 1][currentPos.x] != '#')
		{
			if (pathfindingMap[currentPos.y + 1][currentPos.x] == 0 || pathfindingMap[currentPos.y][currentPos.x] + 1 < pathfindingMap[currentPos.y + 1][currentPos.x])
			{
				pathfindingMap[currentPos.y + 1][currentPos.x] = pathfindingMap[currentPos.y][currentPos.x] + 1;
				pathTile.push_back(t_Pos{ currentPos.x, currentPos.y + 1 });
			}
		}
	}

	finalValue = pathfindingMap[70][70];

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}
