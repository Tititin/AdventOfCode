#include "DayTwo.h"

void dayTwo(const bool& isPartTwo)
{
	FileParser		_file("2016\\InputFiles\\inputD2.txt");
	std::string		line;
	unsigned int	finalValue = 0;
	std::string		partTwoValue = "";

	std::vector<std::string>	keypadPartTwo;

	int				point = 5;
	t_Pos			keyPoint = t_Pos{ 2,0 };

	keypadPartTwo.push_back("..1..");
	keypadPartTwo.push_back(".234.");
	keypadPartTwo.push_back("56789");
	keypadPartTwo.push_back(".ABC.");
	keypadPartTwo.push_back("..D..");

	if (isPartTwo)
		std::cout << "FINAL VALUE = ";

	while ((line = _file.readLineToString()) != "")
	{
		for (int i = 0; i < line.size(); i++)
		{
			switch (line[i])
			{
			case 'U':
				if (!isPartTwo && point - 3 > 0)
					point -= 3;
				else if (isPartTwo && keyPoint.y - 1 >= 0 && keypadPartTwo[keyPoint.y - 1][keyPoint.x] != '.')
					keyPoint.y -= 1;
				break;

			case 'D':
				if (!isPartTwo && point + 3 < 10)
					point += 3;
				else if (isPartTwo && keyPoint.y + 1 < keypadPartTwo.size() && keypadPartTwo[keyPoint.y + 1][keyPoint.x] != '.')
					keyPoint.y += 1;
				break;

			case 'L':
				if (!isPartTwo && point != 1
					&& point != 4
					&& point != 7)
					point -= 1;
				else if (isPartTwo && keyPoint.x - 1 >= 0 && keypadPartTwo[keyPoint.y][keyPoint.x - 1] != '.')
					keyPoint.x -= 1;
				break;

			case 'R':
				if (!isPartTwo && point != 3
					&& point != 6
					&& point != 9)
					point += 1;
				else if (isPartTwo && keyPoint.x + 1 < keypadPartTwo[keyPoint.y].size() && keypadPartTwo[keyPoint.y][keyPoint.x + 1] != '.')
					keyPoint.x += 1;
				break;
			}
		}

		if (!isPartTwo)
		{
			finalValue *= 10;
			finalValue += point;
		}
		else
			std::cout << keypadPartTwo[keyPoint.y][keyPoint.x];
	}

	if (!isPartTwo)
		std::cout << "FINAL VALUE = " << finalValue << std::endl;
	else
		std::cout << std::endl;
}