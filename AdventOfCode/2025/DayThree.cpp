#include "DayThree.h"

void sortVector(std::vector<size_t>& _positions)
{
	bool isSorted = false;

	while (!isSorted)
	{
		isSorted = true;
		for (int i = 0; i < _positions.size() - 1; i++)
		{
			if (_positions[i] > _positions[i + 1])
			{
				size_t	tmp = _positions[i];
				_positions[i] = _positions[i + 1];
				_positions[i + 1] = tmp;
				isSorted = false;
			}
		}
	}
}

void reduceMap(std::map<char, std::vector<size_t>>& _mapPositions)
{
	size_t	minimum = -1;
	char	refNumber = '9';

	// First step of the reduce : we're setting a minimum position and removing previous smaller numbers
	// Ex : in the str "234234234234278", we will remove the first '2' and '3', because we can do better with starting by the first '4'
	for (char c = '9'; c > '0'; c--)
	{
		for (int i = 0; i < _mapPositions[c].size(); i++)
		{
			if (minimum == -1)
			{
				refNumber = c;
				minimum = _mapPositions[c][0];
			}
			else
			{
				
			}
		}
	}
}

void dayThree(const bool& isPartTwo)
{
	FileParser	_fileParser("2025//InputFiles//inputD3bis.txt");
	std::string	line;

	std::vector<std::string>	batteryBanks;
	size_t		maxBatteryPos = 0;

	// PART 1
	std::string		currentJoltageStr = "00";

	// PART 2
	std::map<char, std::vector<size_t>>	numberPositions;
	std::string							maxJoltage = "";


	std::vector<size_t>					biggestNumberPositions;
	std::vector<size_t>					twelveBiggestNumbersPositions;

	unsigned long long int	finalValue = 0;

	while ((line = _fileParser.readLineToString()) != "")
		batteryBanks.push_back(line);

	if (!isPartTwo)
	{
		for (int i = 0; i < batteryBanks.size(); i++)
		{
			std::string	subBank;
			bool		isMaxBatteryFound = false;
			char		startMax = '9';

			while (!isMaxBatteryFound)
			{
				maxBatteryPos = batteryBanks[i].find(startMax);
				if (maxBatteryPos != std::string::npos)
					isMaxBatteryFound = true;
				else
					startMax -= 1;
			}
			if (maxBatteryPos != batteryBanks[i].size() - 1)
			{
				currentJoltageStr[0] = batteryBanks[i][maxBatteryPos];
				subBank = batteryBanks[i].substr(maxBatteryPos + 1);
			}
			else
			{
				currentJoltageStr[1] = batteryBanks[i][maxBatteryPos];
				subBank = batteryBanks[i].substr(0, batteryBanks[i].size() - 1);
			}

			isMaxBatteryFound = false;

			while (!isMaxBatteryFound)
			{
				maxBatteryPos = subBank.find(startMax);
				if (maxBatteryPos != std::string::npos)
					isMaxBatteryFound = true;
				else
					startMax -= 1;
			}
			if (currentJoltageStr[0] == '0')
				currentJoltageStr[0] = subBank[maxBatteryPos];
			else
				currentJoltageStr[1] = subBank[maxBatteryPos];

			finalValue += std::stoull(currentJoltageStr);
			currentJoltageStr = "00";
		}
	}
	else
	{
		for (int i = 0; i < batteryBanks.size(); i++)
		{
			std::vector<size_t>	positions;

			for (char c = '9'; c > '0'; c--)
			{
				size_t	pos = 0;

				while (pos != std::string::npos)
				{
					pos = batteryBanks[i].find(c, pos);
					if (pos != std::string::npos)
					{
						positions.insert(positions.begin(), pos);
						pos += 1;
					}
				}
				numberPositions.insert(std::pair<char, std::vector<size_t>>(c, positions));
				positions.clear();
			}

			for (char c = '9'; c > '0'; c--)
			{
				for (int i = 0; i < numberPositions[c].size(); i++)
					biggestNumberPositions.push_back(numberPositions[c][i]);
			}

			// DEBUG
			std::cout << "POSITION ORDER BY BIGGEST NUMBER FIRST" << std::endl;
			for (int k = 0; k < biggestNumberPositions.size(); k++)
				std::cout << "|" << biggestNumberPositions[k];
			std::cout << std::endl << std::endl;

			for (int j = 0; j < biggestNumberPositions.size(); j++)
			{
				if (biggestNumberPositions[j] + 12 >= biggestNumberPositions.size() - 1)
					twelveBiggestNumbersPositions.push_back(biggestNumberPositions[j]);
			}

			// DEBUG
			std::cout << "AFTER REMOVAL OF TOO SMALLEST NUMBERS" << std::endl;
			for (int k = 0; k < twelveBiggestNumbersPositions.size(); k++)
				std::cout << "|" << twelveBiggestNumbersPositions[k];
			std::cout << std::endl;

			while (twelveBiggestNumbersPositions.size() > 12)
				twelveBiggestNumbersPositions.pop_back();

			// DEBUG
			std::cout << "AFTER REDUCING VECTOR TO 12 BIGGEST NUMBERS" << std::endl;
			for (int k = 0; k < twelveBiggestNumbersPositions.size(); k++)
				std::cout << "|" << twelveBiggestNumbersPositions[k];
			std::cout << std::endl;

			sortVector(twelveBiggestNumbersPositions);

			// DEBUG
			std::cout << "AFTER SORTING VECTOR" << std::endl;
			for (int k = 0; k < twelveBiggestNumbersPositions.size(); k++)
				std::cout << "|" << twelveBiggestNumbersPositions[k];
			std::cout << std::endl;

			for (int j = 0; j < twelveBiggestNumbersPositions.size(); j++)
				maxJoltage += batteryBanks[i][twelveBiggestNumbersPositions[j]];
			std::cout << maxJoltage << std::endl;

			// DEBUG
			/*for (char c = '9'; c > '0'; c--)
			{
				std::cout << c << ": ";
				for (int i = 0; i < numberPositions[c].size(); i++)
					std::cout << numberPositions[c][i] << "|";
				std::cout << std::endl;
			}*/
			std::cout << std::endl << std::endl;
			numberPositions.clear();
			biggestNumberPositions.clear();
			twelveBiggestNumbersPositions.clear();
			maxJoltage = "";
		}
	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}
