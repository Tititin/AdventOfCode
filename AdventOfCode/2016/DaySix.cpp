#include "DaySix.h"

void daySix(const bool& isPartTwo)
{
	FileParser	_file("2016\\InputFiles\\inputD6.txt");
	std::string	line;

	std::string	finalValue = "";

	std::vector<std::string>	inputs;
	std::map<char, int>			letterCount;
	int							maxLetterNumber = 0;
	std::vector<int>			letterCountVector;
	char						letter = 'a';

	while ((line = _file.readLineToString()) != "")
		inputs.push_back(line);

	for (char c = 'a'; c <= 'z'; c++)
		letterCount.insert(std::pair<char, int>(c, 0));

	for (int i = 0; i < inputs[0].size(); i++)
	{
		for (int j = 0; j < inputs.size(); j++)
			letterCount[inputs[j][i]] += 1;

		for (char c = 'a'; c <= 'z'; c++)
		{
			if (!isPartTwo)
			{
				if (letterCount[c] > letterCount[letter])
					letter = c;
			}
			else
				if (letterCount[c] < letterCount[letter])
					letter = c;
		}
		finalValue += letter;
		for (char c = 'a'; c <= 'z'; c++)
			letterCount[c] = 0;
	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}