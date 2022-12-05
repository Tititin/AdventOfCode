#include "DayThree.h"

int		calcPriority(const char& c)
{
	if (c >= 'a' && c <= 'z')
		return (1 + c - 'a');
	else if (c >= 'A' && c <= 'Z')
		return (27 + c - 'A');
}

int		findAndCalcPriority(const std::string& sOne, const std::string& sTwo)
{
	char c;
	bool itemFound = false;

	for (int i = 0; i < sOne.size() && !itemFound; i++)
	{
		for (int j = 0; j < sTwo.size() && !itemFound; j++)
		{
			if (sOne[i] == sTwo[j])
			{
				itemFound = true;
				c = sOne[i];
			}
		}
	}

	return (calcPriority(c));
}

int		findAndCalcPriority(const std::string& sOne, const std::string& sTwo, const std::string& sThree)
{
	char c;
	bool itemFound = false;

	for (int i = 0; i < sOne.size() && !itemFound; i++)
	{
		for (int j = 0; j < sTwo.size() && !itemFound; j++)
		{
			for (int k = 0; k < sThree.size() && !itemFound; k++)
			{
				if (sOne[i] == sTwo[j] && sTwo[j] == sThree[k])
				{
					itemFound = true;
					c = sOne[i];
				}
			}
		}
	}

	return (calcPriority(c));
}

void	dayThree(bool isPartTwo)
{
	FileParser fileParser("..\\inputD3.txt");
	int sumPriority = 0;
	std::string rucksack;

	if (!isPartTwo)
	{
		std::string compartmentOne;
		std::string compartmentTwo;

		while ((rucksack = fileParser.readRucksack()) != "")
		{
			compartmentOne = rucksack.substr(0, rucksack.size() / 2);
			compartmentTwo = rucksack.substr(rucksack.size() / 2, rucksack.size() / 2);

			sumPriority += findAndCalcPriority(compartmentOne, compartmentTwo);
		}

	}
	else
	{
		std::string rucksackOne;
		std::string rucksackTwo;
		std::string rucksackThree;
		int i = 0;

		while ((rucksack = fileParser.readRucksack()) != "")
		{
			if (i % 3 == 0)
			{
				rucksackOne = rucksack;
			}
			else if (i % 3 == 1)
			{
				rucksackTwo = rucksack;
			}
			else
			{
				rucksackThree = rucksack;
				sumPriority += findAndCalcPriority(rucksackOne, rucksackTwo, rucksackThree);
			}
			i++;
		}
	}
	
	std::cout << sumPriority << std::endl;
}