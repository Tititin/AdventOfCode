#include "DayEleven.h"

bool checkIfEmptyRow(const std::string& _row)
{
	for (int i = 0; i < _row.size(); i++)
		if (_row[i] != '.')
			return false;
	return true;
}

bool checkIfEmptyColumn(const std::vector<std::string>& _map, const int& _x)
{
	for (int y = 0; y < _map.size(); y++)
		if (_map[y][_x] != '.')
			return false;
	return true;
}

t_EmptyData countEmptyRowsAndColumns(const std::vector<int>& _emptyRows, const std::vector<int>& _emptyColumns, const t_GalaxyPos& _galaxyA, const t_GalaxyPos& _galaxyB)
{
	t_EmptyData	returnValue = t_EmptyData{ 0, 0 };

	for (int i = 0; i < _emptyColumns.size(); i++)
	{
		if ((_emptyColumns[i] > _galaxyA.x && _emptyColumns[i] < _galaxyB.x)
			|| (_emptyColumns[i] > _galaxyB.x && _emptyColumns[i] < _galaxyA.x))
			returnValue.columns += 1;
	}
	for (int j = 0; j < _emptyRows.size(); j++)
	{
		if ((_emptyRows[j] > _galaxyA.y && _emptyRows[j] < _galaxyB.y)
			|| (_emptyRows[j] > _galaxyB.y && _emptyRows[j] < _galaxyA.y))
			returnValue.rows += 1;
	}

	return returnValue;
}

void dayEleven(const bool& isPartTwo)
{
	FileParser	_fileParser("2023\\InputFiles\\inputD11.txt");
	std::string	line;

	std::vector<std::string>	spaceMap;
	std::vector<int>			emptyColumns;
	std::vector<int>			emptyRows;

	std::vector<t_GalaxyPos>	galaxies;
	t_GalaxyPos					galaxyPos;

	t_EmptyData					emptyRowsAndColumns;

	unsigned long long int			finalValue = 0;

	int							x = 0;
	int							y = 0;

	while ((line = _fileParser.readLineToString()) != "")
	{
		if (checkIfEmptyRow(line))
			emptyRows.push_back(y);
		y += 1;
		spaceMap.push_back(line);
	}
	y = 0;

	while (x < spaceMap[y].size())
	{
		if (checkIfEmptyColumn(spaceMap, x))
			emptyColumns.push_back(x);
		x += 1;
	}

	for (int y = 0; y < spaceMap.size(); y++)
	{
		for (int x = 0; x < spaceMap[y].size(); x++)
		{
			if (spaceMap[y][x] == '#')
				galaxies.push_back(t_GalaxyPos{ x, y });
		}
	}

	unsigned long long int	pathLength = 0;

	for (int i = 0; i < galaxies.size() - 1; i++)
	{
		for (int j = i + 1; j < galaxies.size(); j++)
		{
			emptyRowsAndColumns = countEmptyRowsAndColumns(emptyRows, emptyColumns, galaxies[i], galaxies[j]);
			pathLength = std::abs(galaxies[j].x - galaxies[i].x) + std::abs(galaxies[j].y - galaxies[i].y)
				+ (!isPartTwo ? emptyRowsAndColumns.rows : emptyRowsAndColumns.rows * 999999)
				+ (!isPartTwo ? emptyRowsAndColumns.columns : emptyRowsAndColumns.columns * 999999);
			finalValue += pathLength;
			pathLength = 0;
		}
	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}
