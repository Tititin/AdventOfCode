#include "DayOne.h"

std::vector<std::string> initNumbersArray()
{
	std::vector<std::string> numbers;

	numbers.push_back("zero");
	numbers.push_back("one");
	numbers.push_back("two");
	numbers.push_back("three");
	numbers.push_back("four");
	numbers.push_back("five");
	numbers.push_back("six");
	numbers.push_back("seven");
	numbers.push_back("eight");
	numbers.push_back("nine");

	return numbers;
}

int convertLineToCalibrationValue(std::string& line, const bool &isPartTwo)
{
	int calibrationValue = -1;

	if (isPartTwo)
	{
		std::vector<std::string> numbers = initNumbersArray();
		int index = 0;

		for (int x = 0; x < numbers.size(); x++)
		{
			for (int i = 0; i < line.size(); i++)
			{
				if ((index = line.find(numbers[x], i)) != -1)
					line[index + 1] = x + 48;
			}
		}
	}

	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] >= '0' && line[i] <= '9')
		{
			if (calibrationValue == -1)
				calibrationValue = (line[i] - 48) * 11;
			else
			{
				calibrationValue -= (calibrationValue % 10);
				calibrationValue += (line[i] - 48);
			}
		}
	}
	return calibrationValue;
}

void dayOne(const bool& isPartTwo)
{
	FileParser		_file("2023\\InputFiles\\inputD1.txt");
	std::string		line;
	unsigned int	finalValue = 0;

	while ((line = _file.readLineToString()) != "")
	{
		finalValue += convertLineToCalibrationValue(line, isPartTwo);
	}

	std::cout << finalValue << std::endl;
}
