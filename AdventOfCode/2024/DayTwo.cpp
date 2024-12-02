#include "DayTwo.h"

bool checkIsSorted(const std::vector<int>& _floors, const t_Order& _order)
{
	bool isSorted = true;

	for (int i = 0; i < _floors.size() - 1 && isSorted; i++)
		isSorted = ((_floors[i] <= _floors[i + 1] && _order == ASC)
			|| (_floors[i] >= _floors[i + 1] && _order == DESC));
	
	return isSorted;
}

bool checkFloorDistance(const std::vector<int>& _floors)
{
	bool isFloorNear = true;

	for (int i = 0; i < _floors.size() - 1 && isFloorNear; i++)
	{
		if (abs(_floors[i] - _floors[i + 1]) > 3 || abs(_floors[i] - _floors[i + 1]) < 1)
			isFloorNear = false;
	}

	return isFloorNear;
}

bool analyzeAndRemoveOneLevel(const std::vector<int>& _floors)
{
	bool isFinallySafe = false;

	for (int i = 0; i < _floors.size() && !isFinallySafe; i++)
	{
		std::vector<int> tmp;

		for (int j = 0; j < _floors.size(); j++)
		{
			if (j != i)
				tmp.push_back(_floors[j]);
		}

		isFinallySafe = (checkIsSorted(tmp, ASC) || checkIsSorted(tmp, DESC)) && checkFloorDistance(tmp);
		tmp.clear();
	}

	return isFinallySafe;
}

void dayTwo(const bool& isPartTwo)
{
	FileParser	_file("2024\\InputFiles\\inputD2.txt");
	std::string	line;
	unsigned long long int	finalValue = 0;

	std::vector<std::vector<int>>	floors;
	std::vector<int>				floorLine;
	int								floorNumber = 0;

	while ((line = _file.readLineToString()) != "")
	{
		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] >= '0' && line[i] <= '9')
				floorNumber = floorNumber * 10 + line[i] - '0';
			else
			{
				floorLine.push_back(floorNumber);
				floorNumber = 0;
			}
		}
		floorLine.push_back(floorNumber);
		floorNumber = 0;
		floors.push_back(floorLine);
		floorLine.clear();
	}

	for (int i = 0; i < floors.size(); i++)
	{
		if ((checkIsSorted(floors[i], ASC) || checkIsSorted(floors[i], DESC))
			&& checkFloorDistance(floors[i]))
			finalValue += 1;
		else if (isPartTwo && analyzeAndRemoveOneLevel(floors[i]))
			finalValue += 1;
	}

	//std::cout << "INPUT SIZE = " << floors.size() << std::endl;
	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}