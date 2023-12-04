#include "DayThree.h"

bool checkSymbolNearNumber(std::vector<std::string>& _map, const t_Coor& _start, const t_Coor& _end, std::vector<t_Gear>& _gears, const int& nbr, const bool& isPartTwo)
{
	int x = 0;
	int y = 0;
	bool symbolFound = false;

	if (_start.x != 0)
		x = _start.x - 1;
	if (_start.y != 0)
		y = _start.y - 1;

	while (y < _end.y + 2 && y < _map.size() && !symbolFound)
	{
		if (_map[y][x] != '.' && (_map[y][x] < '0' || _map[y][x] > '9'))
		{
			if (isPartTwo)
			{
				if (_map[y][x] == '*')
				{
					t_Gear newGear;

					newGear.number = nbr;
					newGear.x = x;
					newGear.y = y;
					_gears.push_back(newGear);
				}
			}
			symbolFound = true;
		}
		x += 1;
		if (x == _end.x + 2 || x == _map[y].size())
		{
			if (_start.x != 0)
				x = _start.x - 1;
			else
				x = 0;
			y += 1;
		}
	}

	return symbolFound;
}

void checkGears(std::vector<t_Gear>& _gears, int& finalValue)
{
	int	nbA;
	int	nbB;

	int	i = 0;
	int	j = i + 1;

	while (i < _gears.size())
	{
		while (j < _gears.size())
		{
			if (_gears[i].x == _gears[j].x && _gears[i].y == _gears[j].y && !_gears[i].isChecked && !_gears[j].isChecked)
			{
				nbA = _gears[i].number;
				nbB = _gears[j].number;

				finalValue = finalValue + (nbA * nbB);

				_gears[i].isChecked = true;
				_gears[j].isChecked = true;
			}
			j += 1;
		}
		i += 1;
		j = i + 1;
	}
}

std::vector<std::string> initFileMap(FileParser& _fileParser)
{
	std::vector<std::string>	fileMap;
	std::string					line;

	while ((line = _fileParser.readLineToString()) != "")
		fileMap.push_back(line);

	return fileMap;
}

void dayThree(const bool& isPartTwo)
{
	FileParser	_fileParser("2023\\InputFiles\\inputD3.txt");
	std::vector<std::string>	fileMap;

	bool		numberFound = false;

	t_Coor		numberStartPos;
	t_Coor		numberEndPos;

	int			tmpNumber = 0;

	std::vector<t_Gear>	gears;

	int			finalValue = 0;

	fileMap = initFileMap(_fileParser);

	for (int y = 0; y < fileMap.size(); y++)
	{
		for (int i = 0; i < fileMap[y].size(); i++)
		{
			if (fileMap[y][i] >= '0' && fileMap[y][i] <= '9')
			{
				if (!numberFound)
				{
					numberStartPos.x = i;
					numberStartPos.y = y;
					numberFound = true;
				}
				tmpNumber = tmpNumber * 10 + (fileMap[y][i] - 48);
			}
			else if (numberFound)
			{
				numberEndPos.x = i - 1;
				numberEndPos.y = y;
				if (checkSymbolNearNumber(fileMap, numberStartPos, numberEndPos, gears, tmpNumber, isPartTwo))
					finalValue += tmpNumber;
				tmpNumber = 0;
				numberFound = false;
			}
		}
	}

	if (isPartTwo)
	{
		finalValue = 0;
		checkGears(gears, finalValue);
	}
	std::cout << finalValue << std::endl;
}
