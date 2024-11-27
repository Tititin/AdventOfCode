#include "DayTwentyOne.h"

void updateTile(std::vector<std::vector<t_GardenTileType>>& _garden, t_Pos& _pos, unsigned int _steps)
{

}

void dayTwentyOne(const bool& isPartTwo)
{
	FileParser	_fileParser("2023\\InputFiles\\inputD21bis.txt");
	std::string	line;

	std::vector<std::string>		gardenMap;
	std::vector<std::vector<t_GardenTileType>>	gardenTypeMap;

	t_Pos	start;
	unsigned int	steps = 6;

	unsigned long long int		finalValue = 0;

	while ((line = _fileParser.readLineToString()) != "")
	{
		gardenMap.push_back(line);
		gardenTypeMap.push_back(std::vector<t_GardenTileType>(line.size(), EMPTY));
	}

	for (int y = 0; y < gardenTypeMap.size(); y++)
	{
		for (int x = 0; x < gardenTypeMap[y].size(); x++)
		{
			if (gardenMap[y][x] == '#')
				gardenTypeMap[y][x] = ROCK;
			else if (gardenMap[y][x] == 'S')
				start = t_Pos{ x, y };
		}
	}

	for (int y = 0; y < gardenMap.size(); y++)
	{
		for (int x = 0; x < gardenMap[y].size(); x++)
		{
			unsigned int distance = std::abs(start.y - y) + std::abs(start.x - x);

			if (distance <= steps && distance % 2 == 0)
			{
				if (gardenTypeMap[y][x] == EMPTY)
				{
					gardenTypeMap[y][x] = EVEN;
					finalValue += 1;
				}
			}
		}
	}

	for (int y = 0; y < gardenMap.size(); y++)
	{
		for (int x = 0; x < gardenMap[y].size(); x++)
		{
			switch (gardenTypeMap[y][x])
			{
			case EMPTY:
				std::cout << ".";
				break;
			case ROCK:
				std::cout << "#";
				break;
			case EVEN:
				std::cout << "O";
				break;
			}
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}
