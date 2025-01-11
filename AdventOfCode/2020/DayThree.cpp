#include "DayThree.h"

void dayThree(const bool& isPartTwo)
{
	FileParser	_file("2020\\InputFiles\\inputD3.txt");
	std::string	line;
	unsigned long long int	finalValue = 1;

	std::vector<std::string>	slopeMap;
	t_Pos						currentPos = t_Pos{ 0, 0 };
	std::vector<t_Pos>			moveVectors;

	while ((line = _file.readLineToString()) != "")
		slopeMap.push_back(line);

	moveVectors.push_back(t_Pos{ 3, 1 });

	if (isPartTwo)
	{
		moveVectors.push_back(t_Pos{ 1, 1 });
		moveVectors.push_back(t_Pos{ 5, 1 });
		moveVectors.push_back(t_Pos{ 7, 1 });
		moveVectors.push_back(t_Pos{ 1, 2 });
	}

	for (t_Pos moveVector : moveVectors)
	{
		int trees = 0;

		currentPos = t_Pos{ 0, 0 };
		do
		{
			currentPos.x = (currentPos.x + moveVector.x) % slopeMap[currentPos.y].size();
			currentPos.y += moveVector.y;
			if (slopeMap[currentPos.y][currentPos.x] == '#')
				trees += 1;
		} while (currentPos.y + moveVector.y < slopeMap.size());

		finalValue *= trees;
	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}