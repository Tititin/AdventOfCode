#include "DayTwo.h"

void dayTwo(const bool& isPartTwo)
{
	FileParser	_file("2020\\InputFiles\\inputD2.txt");
	std::string	word;
	unsigned long long int	finalValue = 0;

	unsigned int	min = 0;
	unsigned int	max = 0;
	char			letter;

	while ((word = _file.readWordToString()) != "")
	{
		if (word.find('-') != std::string::npos)
		{
			int	index = 0;

			//std::cout << word << std::endl;
			while (word[index] != '-')
				min = min * 10 + word[index++] - '0';
			index += 1;
			while (index < word.size())
				max = max * 10 + word[index++] - '0';
		}
		else if (word.find(':') != std::string::npos)
		{
			letter = word[0];
		}
		else
		{
			int	count = 0;

			//std::cout << "LOOKING FOR MIN = " << min << " AND MAX = " << max << std::endl;

			if (!isPartTwo)
			{
				for (int i = 0; i < word.size(); i++)
				{
					if (word[i] == letter)
						count += 1;
				}
				if (count >= min && count <= max)
					finalValue += 1;
			}
			else
			{
				if ((word[min - 1] == letter && word[max - 1] != letter)
					|| (word[min - 1] != letter && word[max - 1] == letter))
					finalValue += 1;
			}

			min = 0;
			max = 0;
		}
	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}