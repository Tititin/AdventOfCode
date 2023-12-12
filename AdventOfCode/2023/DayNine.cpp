#include "DayNine.h"

bool checkIfAllZero(std::vector<long long int>& line)
{
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] != 0)
			return false;
	}
	return true;
}

void calcFinalValue(std::vector<std::vector<long long int>>& dataNumbers, long long int& finalValue, const bool& isPartTwo)
{
	int	i = 0;

	while (i != dataNumbers.size() && !checkIfAllZero(dataNumbers[i]))
	{
		std::vector<long long int>	line;
		for (int x = 0; x < dataNumbers[i].size() - 1; x++)
		{
			long long int tmp = dataNumbers[i][x + 1] - dataNumbers[i][x];
			line.push_back(tmp);
		}
		dataNumbers.push_back(line);
		line.clear();
		i += 1;
	}
	while (i >= 0)
	{
		if (i == dataNumbers.size() - 1)
			dataNumbers[i].push_back(0);
		else
		{
			long long int val;

			if (!isPartTwo)
				val = dataNumbers[i + 1][dataNumbers[i + 1].size() - 1];
			else
				val = dataNumbers[i + 1][0];

			if (!isPartTwo)
				dataNumbers[i].push_back(dataNumbers[i][dataNumbers[i].size() - 1] + val);
			else
				dataNumbers[i].insert(dataNumbers[i].begin(), dataNumbers[i][0] - val);
			if (i == 0)
			{
				if (!isPartTwo)
					finalValue += dataNumbers[i][dataNumbers[i].size() - 1];
				else
					finalValue += dataNumbers[i][0];
			}
		}
		i--;
	}
}

void dayNine(const bool& isPartTwo)
{
	FileParser	_fileParser("2023\\InputFiles\\inputD9.txt");
	std::string	word;

	std::vector<std::vector<long long int> > dataNumbers;
	std::vector<long long int>				dataLine;

	long long int	finalValue = 0;
	int				size = 0;

	while ((word = _fileParser.readWordToString()) != "")
	{
		dataLine.push_back(std::stol(word));
		size += 1;

		if (size == 21) // HARD CODED, WARNING ! MUST CHANGE EITHER YOU USE EXAMPLE OR REAL FILE (Yep, that's dirty)
		{
			dataNumbers.push_back(dataLine);
			size = 0;
			calcFinalValue(dataNumbers, finalValue, isPartTwo);
			dataLine.clear();
			dataNumbers.clear();
		}
	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}
