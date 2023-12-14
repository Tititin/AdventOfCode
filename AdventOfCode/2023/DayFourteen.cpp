#include "DayFourteen.h"

void rollNorth(std::vector<std::string>& _rockMap)
{
	for (int y = 1; y < _rockMap.size(); y++)
	{
		for (int x = 0; x < _rockMap[y].size(); x++)
		{
			if (_rockMap[y][x] == 'O')
			{
				int i = y;

				while (i - 1 >= 0 && _rockMap[i - 1][x] == '.')
					i -= 1;
				_rockMap[y][x] = '.';
				_rockMap[i][x] = 'O';
			}
		}
	}
}

void rollSouth(std::vector<std::string>& _rockMap)
{
	for (int y = _rockMap.size() - 1; y >= 0; y--)
	{
		for (int x = 0; x < _rockMap[y].size(); x++)
		{
			if (_rockMap[y][x] == 'O')
			{
				int i = y;

				while (i + 1 < _rockMap.size() && _rockMap[i + 1][x] == '.')
					i += 1;
				_rockMap[y][x] = '.';
				_rockMap[i][x] = 'O';
			}
		}
	}
}

void rollEast(std::vector<std::string>& _rockMap)
{
	for (int y = 0; y < _rockMap.size(); y++)
	{
		for (int x = _rockMap.size() - 2; x >= 0; x--)
		{
			if (_rockMap[y][x] == 'O')
			{
				int i = x;

				while (i + 1 < _rockMap[y].size() && _rockMap[y][i + 1] == '.')
					i += 1;
				_rockMap[y][x] = '.';
				_rockMap[y][i] = 'O';
			}
		}
	}
}

void rollWest(std::vector<std::string>& _rockMap)
{
	for (int y = 0; y < _rockMap.size(); y++)
	{
		for (int x = 1; x < _rockMap.size(); x++)
		{
			if (_rockMap[y][x] == 'O')
			{
				int i = x;

				while (i - 1 >= 0 && _rockMap[y][i - 1] == '.')
					i -= 1;
				_rockMap[y][x] = '.';
				_rockMap[y][i] = 'O';
			}
		}
	}
}

void dayFourteen(const bool& isPartTwo)
{
	FileParser	_fileParser("2023\\InputFiles\\inputD14.txt");
	std::string	line;

	std::vector<std::string>	rockMap;

	std::map<std::vector<std::string>, int>	cycleMaps;
	int										cycle = 0;

	unsigned long long int		finalValue = 0;

	while ((line = _fileParser.readLineToString()) != "")
		rockMap.push_back(line);

	if (!isPartTwo)
		rollNorth(rockMap);
	else
	{
		for (int i = 0; i < 1000000000; i++)
		{
			rollNorth(rockMap);
			rollWest(rockMap);
			rollSouth(rockMap);
			rollEast(rockMap);

			if (cycleMaps.find(rockMap) == cycleMaps.end())
			{
				cycleMaps.insert(std::pair<std::vector<std::string>, int>(rockMap, cycle));
				cycle += 1;
			}
			else
			{
				int		period = cycle - cycleMaps[rockMap];

				while (i + period < 1000000000)
					i += period;
			}
		}
	}

	for (int y = 0; y < rockMap.size(); y++)
	{
		int nb = 0;

		for (int x = 0; x < rockMap[y].size(); x++)
		{
			if (rockMap[y][x] == 'O')
				nb += 1;
		}
		finalValue += nb * (rockMap.size() - y);
	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}
