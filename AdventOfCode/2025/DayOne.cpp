#include "DayOne.h"

void dayOne(const bool& isPartTwo)
{
	FileParser	_fileParser("2025//InputFiles//inputD1.txt");
	std::string	line;

	int			currentPos = 50;
	bool		startingAtZero = false;

	unsigned long long int	finalValue = 0;

	while ((line = _fileParser.readLineToString()) != "")
	{
		if (isPartTwo)
			finalValue += (std::stoi(line.substr(1)) / 100);
		if (line[0] == 'L')
		{
			currentPos -= (std::stoi(line.substr(1))) % 100;
			if (currentPos < 0)
			{
				if (isPartTwo && !startingAtZero)
					finalValue += 1;
				currentPos = 100 + currentPos;
			}
		}
		else
		{
			currentPos += (std::stoi(line.substr(1))) % 100;
			if (currentPos >= 100)
			{
				if (isPartTwo && currentPos % 100 != 0)
					finalValue += 1;
				currentPos = currentPos % 100;
			}
		}
		if (currentPos == 0 && !startingAtZero)
		{
			finalValue += 1;
			startingAtZero = true;
		}
		else if (currentPos != 0)
			startingAtZero = false;
	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}
