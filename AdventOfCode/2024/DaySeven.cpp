#include "DaySeven.h"

unsigned long long int combineOperator(const unsigned long long int& _left, const unsigned long long int& _right)
{
	std::string	leftStr = std::to_string(_left);
	std::string	rightStr = std::to_string(_right);
	std::string	result = leftStr + rightStr;

	return (std::stoull(result));
}

unsigned long long int findAllOperations(const long long int& _nbToFind, const std::vector<unsigned long long int>& _numbers, const bool& isPartTwo)
{
	std::string		binaryNumber = "";
	unsigned int	opNumber = 0;
	std::string		opString = "";

	long long int	nb = 0;
	int				power = 0;

	unsigned long long int	result = 0;
	bool					equationSolved = false;

	for (int i = 0; i < _numbers.size() - 1; i++) // 2 numbers to analyze, so 1 operator. 5 numbers ? 4 operators.
		opString += "+";

	if (!isPartTwo)
		power = 2;
	else
		power = 3;

	while (opNumber < pow(power, opString.size()) && !equationSolved) // 4 operators, so 2^4 possibilities, so 16 possibilities from 0 to 15
	{
		unsigned int	tmp = opNumber;

		if (!isPartTwo)
		{
			while (binaryNumber.size() < opString.size()) // Convert decimal number into a binary string number (12 = 1100)
			{
				binaryNumber.insert(binaryNumber.begin(), tmp % 2 + '0');
				if (tmp % 2 == 1)
					tmp -= 1;
				tmp /= 2;
			}
		}
		else
		{
			while (binaryNumber.size() < opString.size()) // Convert decimal number into a binary string number (12 = 1100)
			{
				binaryNumber.insert(binaryNumber.begin(), tmp % 3 + '0');
				if (tmp % 3 != 0)
					tmp -= tmp % 3;
				tmp /= 3;
			}
		}

		if (binaryNumber[0] == '0' && binaryNumber.size() > opString.size()) // If binary number is like '01100', remove the first character to keep '1100'. If binaryNumber == 0, don't remove anything
			binaryNumber.erase(binaryNumber.begin());
		else if (binaryNumber.size() == 0)
			binaryNumber += '0';

		for (int i = 0; i < binaryNumber.size(); i++) // Use binary number to define the list of operators (0 = '+', 1 = '*')
		{
			if (binaryNumber[i] == '0')
				opString[i] = '+';
			else if (binaryNumber[i] == '1')
				opString[i] = '*';
			else
				opString[i] = '|';
		}

		nb = _numbers[0]; // Since it's left-to-right operations, we take the first number

		for (int i = 0; i < opString.size(); i++) // While we didn't used all operators, let's add/multiply values
		{
			if (opString[i] == '+')
				nb += _numbers[i + 1];
			else if (opString[i] == '*')
				nb *= _numbers[i + 1];
			else
				nb = combineOperator(nb, _numbers[i + 1]);
		}

		if (nb == _nbToFind) // If result is equal to the number to find
		{
			result = _nbToFind;
			equationSolved = true;
		}

		opNumber += 1;
		binaryNumber = ""; // Reset binary number so we can change operator list
	}

	return result;
}

void daySeven(const bool& isPartTwo)
{
	FileParser	_file("2024\\InputFiles\\inputD7.txt");
	std::string	word;
	unsigned long long int	finalValue = 0;

	std::vector<unsigned long long int>	numbers;
	long long int				numberToFind = -1;
	long long int				nb = 0;

	while ((word = _file.readWordToString()) != "")
	{
		for (int i = 0; i < word.size() - 1 && word[i] != ':'; i++)
			nb = nb * 10 + (word[i] - '0');
		if (word[word.size() - 1] != ':')
			nb = nb * 10 + (word[word.size() - 1] - '0');

		if (word.find(':') != std::string::npos)
		{
			if (numberToFind != -1)
			{
				finalValue += findAllOperations(numberToFind, numbers, isPartTwo);
				numbers.clear();
			}
			numberToFind = nb;
		}
		else
			numbers.push_back(nb);
		nb = 0;
	}

	finalValue += findAllOperations(numberToFind, numbers, isPartTwo);

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}