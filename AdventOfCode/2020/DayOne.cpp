#include "DayOne.h"

void dayOne(const bool& isPartTwo)
{
	FileParser	_file("2020\\InputFiles\\inputD1.txt");
	std::string	line;
	unsigned long long int	finalValue = 0;

	std::vector<int>	expenses;

	while ((line = _file.readLineToString()) != "")
	{
		int	value = std::stoi(line);

		expenses.push_back(value);
	}

	if (!isPartTwo)
	{
		for (int i = 0; i < expenses.size() - 1; i++)
		{
			for (int j = i + 1; j < expenses.size(); j++)
			{
				if (expenses[i] + expenses[j] == 2020)
					finalValue = expenses[i] * expenses[j];
			}
		}
	}
	else
	{
		for (int x = 0; x < expenses.size() - 2; x++)
		{
			for (int y = x + 1; y < expenses.size() - 1; y++)
			{
				for (int z = y + 1; z < expenses.size(); z++)
				{
					if (expenses[x] + expenses[y] + expenses[z] == 2020)
						finalValue = expenses[x] * expenses[y] * expenses[z];
				}
			}
		}
	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}