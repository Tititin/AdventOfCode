#include "DayFive.h"

bool vowelsCheck(const std::string& _str)
{
	std::string vowels = "aeiou";
	int nbVowels = 0;

	for (int i = 0; i < _str.size(); i++)
	{
		if (vowels.find(_str[i]) != std::string::npos)
			nbVowels += 1;
	}
	return (nbVowels >= 3);
}

bool doubleLetterCheck(const std::string& _str)
{
	bool doubleLetter = false;

	for (int i = 0; i < _str.size() - 1 && !doubleLetter; i++)
	{
		if (_str[i] == _str[i + 1])
			doubleLetter = true;
	}
	return doubleLetter;
}

bool forbiddenStringsCheck(const std::string& _str)
{
	if (_str.find("ab") != std::string::npos
		|| _str.find("cd") != std::string::npos
		|| _str.find("pq") != std::string::npos
		|| _str.find("xy") != std::string::npos)
		return false;
	return true;
}

bool doublePairLetters(const std::string& _str)
{
	std::vector<int>	letterPos;
	bool				doublePair = false;

	for (int i = 0; i < _str.size() - 1 && !doublePair; i++)
	{
		for (int j = i + 2; j < _str.size() - 1 && !doublePair; j++)
		{
			if (_str[j] == _str[i]
				&& _str[j + 1] == _str[i + 1])
				doublePair = true;
		}
	}

	return doublePair;
}

bool doubleLetterWithOneBetweenCheck(const std::string& _str)
{
	bool doubleLetter = false;

	for (int i = 0; i < _str.size() - 2 && !doubleLetter; i++)
	{
		if (_str[i] == _str[i + 2])
			doubleLetter = true;
	}
	return doubleLetter;
}

void dayFive(const bool& isPartTwo)
{
	FileParser		_file("2015\\InputFiles\\inputD5.txt");
	std::string		line;
	unsigned int	finalValue = 0;

	while ((line = _file.readLineToString()) != "")
	{
		if (!isPartTwo && vowelsCheck(line) && doubleLetterCheck(line) && forbiddenStringsCheck(line))
			finalValue += 1;
		else if (isPartTwo && doubleLetterWithOneBetweenCheck(line) && doublePairLetters(line))
			finalValue += 1;
	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}