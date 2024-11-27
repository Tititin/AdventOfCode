#include "DayOne.h"

void dayOne(const bool& isPartTwo)
{
	FileParser		_file("2015\\InputFiles\\inputD1.txt");
	std::string		line;
	unsigned int	finalValue = 0;

	line = _file.readLineToString();

	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] == '(')
			finalValue += 1;
		else
			finalValue -= 1;

		if (isPartTwo && finalValue == -1)
		{
			finalValue = i + 1;
			break;
		}
	}

	std::cout << finalValue << std::endl;
}