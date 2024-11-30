#include "DayThree.h"

int checkPossibleTriangle(const std::vector<int>& _triangle)
{
	if (_triangle[0] + _triangle[1] <= _triangle[2]
		|| _triangle[1] + _triangle[2] <= _triangle[0]
		|| _triangle[2] + _triangle[0] <= _triangle[1])
		return 0;
	else
		return 1;
}

void dayThree(const bool& isPartTwo)
{
	FileParser			_file("2016\\InputFiles\\inputD3.txt");
	std::string			numberString;
	unsigned int		finalValue = 0;

	std::vector<int>	triangleSides;

	//PART 2
	std::vector<std::vector<int>>	threeTrianglesSides;
	int								count = 0;

	threeTrianglesSides.push_back(triangleSides);
	threeTrianglesSides.push_back(triangleSides);
	threeTrianglesSides.push_back(triangleSides);

	while ((numberString = _file.readWordToString()) != "")
	{
		int number = std::stoi(numberString);

		if (isPartTwo)
		{
			if (count != 0 && count % 9 == 0)
			{
				for (int i = 0; i < threeTrianglesSides.size(); i++)
				{
					finalValue += checkPossibleTriangle(threeTrianglesSides[i]);
					threeTrianglesSides[i].clear();
				}
			}
			threeTrianglesSides[count % 3].push_back(number);
		}
		else
		{
			if (triangleSides.size() < 3)
				triangleSides.push_back(number);
			if (triangleSides.size() == 3)
			{
				finalValue += checkPossibleTriangle(triangleSides);
				triangleSides.clear();
			}
		}

		count += 1;
	}

	if (isPartTwo)
	{
		for (int i = 0; i < threeTrianglesSides.size(); i++)
		{
			finalValue += checkPossibleTriangle(threeTrianglesSides[i]);
			threeTrianglesSides[i].clear();
		}
	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}