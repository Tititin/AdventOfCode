#include "DayFour.h"

int checkHorizontally(const std::string& _line, const t_Pos& _pos)
{
	int		nbFound = 0;

	if (_pos.x + 3 < _line.size())
	{
		if (_line[_pos.x + 1] == 'M' && _line[_pos.x + 2] == 'A' && _line[_pos.x + 3] == 'S')
		{
			std::cout << "FOUND AT STARTPOS " << _pos.x << ";" << _pos.y << " TO THE RIGHT" << std::endl;
			nbFound += 1;
		}
	}
	if (_pos.x - 3 >= 0)
	{
		if (_line[_pos.x - 1] == 'M' && _line[_pos.x - 2] == 'A' && _line[_pos.x - 3] == 'S')
		{
			std::cout << "FOUND AT STARTPOS " << _pos.x << ";" << _pos.y << " TO THE LEFT" << std::endl;
			nbFound += 1;
		}
	}

	return nbFound;
}

int checkVertically(const std::vector<std::string>& _map, const t_Pos& _pos)
{
	int		nbFound = 0;

	if (_pos.y + 3 < _map.size())
	{
		if (_map[_pos.y + 1][_pos.x] == 'M' && _map[_pos.y + 2][_pos.x] == 'A' && _map[_pos.y + 3][_pos.x] == 'S')
		{
			std::cout << "FOUND AT STARTPOS " << _pos.x << ";" << _pos.y << " DOWNWARDS" << std::endl;
			nbFound += 1;
		}
	}
	if (_pos.y - 3 >= 0)
	{
		if (_map[_pos.y - 1][_pos.x] == 'M' && _map[_pos.y - 2][_pos.x] == 'A' && _map[_pos.y - 3][_pos.x] == 'S')
		{
			std::cout << "FOUND AT STARTPOS " << _pos.x << ";" << _pos.y << " UPWARDS" << std::endl;
			nbFound += 1;
		}
	}

	return nbFound;
}

int checkDiagonally(const std::vector<std::string>& _map, const t_Pos& _pos)
{
	int		nbFound = 0;

	if (_pos.y + 3 < _map.size() && (_pos.x >= 3 || _pos.x <= _map[_pos.y].size() - 4))
	{
		if (_pos.x <= _map[_pos.y].size() - 4 && _map[_pos.y + 1][_pos.x + 1] == 'M' && _map[_pos.y + 2][_pos.x + 2] == 'A' && _map[_pos.y + 3][_pos.x + 3] == 'S')
			nbFound += 1;
		if (_pos.x >= 3 && _map[_pos.y + 1][_pos.x - 1] == 'M' && _map[_pos.y + 2][_pos.x - 2] == 'A' && _map[_pos.y + 3][_pos.x - 3] == 'S')
			nbFound += 1;
	}
	if (_pos.y - 3 >= 0 && (_pos.x >= 3 || _pos.x <= _map[_pos.y].size() - 4))
	{
		if (_pos.x <= _map[_pos.y].size() - 4 && _map[_pos.y - 1][_pos.x + 1] == 'M' && _map[_pos.y - 2][_pos.x + 2] == 'A' && _map[_pos.y - 3][_pos.x + 3] == 'S')
			nbFound += 1;
		if (_pos.x >= 3 && _map[_pos.y - 1][_pos.x - 1] == 'M' && _map[_pos.y - 2][_pos.x - 2] == 'A' && _map[_pos.y - 3][_pos.x - 3] == 'S')
			nbFound += 1;
	}

	return nbFound;
}

int checkCross(const std::vector<std::string>& _map, const t_Pos& _pos)
{
	if (_pos.x == 0 || _pos.y == 0)
		return (0);
	else if (_pos.x == _map[_pos.y].size() - 1 || _pos.y == _map.size() - 1)
		return (0);
	else if (_map[_pos.y - 1][_pos.x - 1] == 'M' && _map[_pos.y + 1][_pos.x + 1] == 'S')
	{
		if (_map[_pos.y - 1][_pos.x + 1] == 'M' && _map[_pos.y + 1][_pos.x - 1] == 'S')
			return (1);
		else if (_map[_pos.y - 1][_pos.x + 1] == 'S' && _map[_pos.y + 1][_pos.x - 1] == 'M')
			return (1);
	}
	else if (_map[_pos.y - 1][_pos.x - 1] == 'S' && _map[_pos.y + 1][_pos.x + 1] == 'M')
	{
		if (_map[_pos.y - 1][_pos.x + 1] == 'M' && _map[_pos.y + 1][_pos.x - 1] == 'S')
			return (1);
		else if (_map[_pos.y - 1][_pos.x + 1] == 'S' && _map[_pos.y + 1][_pos.x - 1] == 'M')
			return (1);
	}
	return (0);
}

void dayFour(const bool& isPartTwo)
{
	FileParser	_file("2024\\InputFiles\\inputD4.txt");
	std::string	line;
	unsigned long int	finalValue = 0;

	std::vector<std::string>	fileMap;

	while ((line = _file.readLineToString()) != "")
		fileMap.push_back(line);

	for (int y = 0; y < fileMap.size(); y++)
	{
		for (int x = 0; x < fileMap[y].size(); x++)
		{
			if (!isPartTwo && fileMap[y][x] == 'X')
			{
				finalValue += checkHorizontally(fileMap[y], t_Pos{ x, y });
				finalValue += checkVertically(fileMap, t_Pos{ x, y });
				finalValue += checkDiagonally(fileMap, t_Pos{ x, y });
			}
			else if (isPartTwo && fileMap[y][x] == 'A')
				finalValue += checkCross(fileMap, t_Pos{ x, y });
		}
	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}