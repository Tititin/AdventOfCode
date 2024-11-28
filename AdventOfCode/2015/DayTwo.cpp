#include "DayTwo.h"

unsigned long long int findSmallestAreaSize(const std::vector<int>& _dimensions)
{
	unsigned long long int a = _dimensions[0] * _dimensions[1];
	unsigned long long int b = _dimensions[1] * _dimensions[2];
	unsigned long long int c = _dimensions[2] * _dimensions[0];

	if (a <= b && a <= c)
		return (a);
	else if (b <= a && b <= c)
		return (b);
	else
		return (c);
}

unsigned long long int findSmallestPerimeterSize(const std::vector<int>& _dimensions)
{
	unsigned long long int perimeterA = 2 * _dimensions[0] + 2 * _dimensions[1];
	unsigned long long int perimeterB = 2 * _dimensions[1] + 2 * _dimensions[2];
	unsigned long long int perimeterC = 2 * _dimensions[2] + 2 * _dimensions[0];

	if (perimeterA <= perimeterB && perimeterA <= perimeterC)
		return (perimeterA);
	else if (perimeterB <= perimeterA && perimeterB <= perimeterC)
		return (perimeterB);
	else
		return (perimeterC);
}

unsigned long long int calcBow(const std::vector<int>& _dimensions)
{
	unsigned long long int bow = 1;

	for (int i = 0; i < _dimensions.size(); i++)
		bow *= _dimensions[i];

	return (bow);
}

void dayTwo(const bool& isPartTwo)
{
	FileParser		_file("2015\\InputFiles\\inputD2.txt");
	std::string		line;
	unsigned long long int	finalValue = 0;

	std::vector<int>	dimensions;
	unsigned long long int addedValue = 0;

	while ((line = _file.readLineToString()) != "")
	{
		int tmp = 0;

		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] != 'x')
			{
				tmp *= 10;
				tmp += line[i] - '0';
			}
			else
			{
				dimensions.push_back(tmp);
				tmp = 0;
			}
		}
		dimensions.push_back(tmp);
		if (!isPartTwo)
			addedValue = 2 * dimensions[0] * dimensions[1] + 2 * dimensions[1] * dimensions[2] + 2 * dimensions[2] * dimensions[0] + findSmallestAreaSize(dimensions);
		else
			addedValue = findSmallestPerimeterSize(dimensions) + calcBow(dimensions);
		finalValue += addedValue;
		dimensions.clear();
	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}