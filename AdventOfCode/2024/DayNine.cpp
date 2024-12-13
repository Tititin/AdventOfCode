#include "DayNine.h"

void dayNine(const bool& isPartTwo)
{
	FileParser	_file("2024\\InputFiles\\inputD9.txt");
	std::string	line;
	unsigned long long int finalValue = 0;

	unsigned int	fileID = 0;
	bool			isFreeSpace = false;
	std::string		driveMap;
	std::vector<long long int>	driveMapVector;
	std::vector<std::vector<long long int>>	driveMapPartTwo;

	line = _file.readLineToString();

	for (int i = 0; i < line.size(); i++)
	{
		if (!isFreeSpace)
		{
			for (int x = 0; x < line[i] - '0'; x++)
				driveMapVector.push_back(fileID);
			fileID += 1;
			if (isPartTwo)
			{
				driveMapPartTwo.push_back(driveMapVector);
				driveMapVector.clear();
			}
		}
		else
		{
			for (int x = 0; x < line[i] - '0'; x++)
				driveMapVector.push_back(-1);
			if (isPartTwo)
			{
				driveMapPartTwo.push_back(driveMapVector);
				driveMapVector.clear();
			}
		}
		isFreeSpace = !isFreeSpace;
	}

	std::cout << fileID << " FILES FOUND" << std::endl;

	if (!isPartTwo)
	{
		for (int x = 0, y = driveMapVector.size() - 1; x < y; x++, y--)
		{
			if (driveMapVector[x] == -1 && driveMapVector[y] != -1)
			{
				long long int c = driveMapVector[x];
				driveMapVector[x] = driveMapVector[y];
				driveMapVector[y] = c;
			}
			else if (driveMapVector[x] != -1 && driveMapVector[y] != -1)
				y += 1;
			else
				x -= 1;
		}
	}
	else
	{
		for (int x = 0, y = driveMapPartTwo.size() - 1; x < y; x++, y--)
		{
			if (driveMapPartTwo[x][0] == -1 && driveMapPartTwo[x].size() >= driveMapPartTwo[y].size() && driveMapPartTwo[y][0] != -1)
			{
				bool isDifferentSize = driveMapPartTwo[x].size() >= driveMapPartTwo[y].size();
				unsigned long long int	difference;

				if (isDifferentSize)
					difference = driveMapPartTwo[x].size() - driveMapPartTwo[y].size();

				std::vector<long long int>	tmp = driveMapPartTwo[x];
				driveMapPartTwo[x] = driveMapPartTwo[y];
				driveMapPartTwo[y] = tmp;

				if (isDifferentSize)
					driveMapPartTwo.insert(driveMapPartTwo.begin() + x, std::vector<long long int>(difference, -1));
				x = 0;
			}
			else if (driveMapPartTwo[x][0] != -1 && driveMapPartTwo[y][0] != -1)
				y += 1;
		}
	}

	for (int i = 0; i < driveMapVector.size() && driveMapVector[i] != -1; i++)
		finalValue += driveMapVector[i] * i;

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}
