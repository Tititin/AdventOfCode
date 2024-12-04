#include "DayThree.h"

bool checkIfMulExpression(int pos, const std::string& str)
{
	bool	isMul = true;
	std::string	pattern = "mul(";

	for (int i = 0; i < str.size() && isMul; i++)
	{
		continue;
	}

	return false;
}

unsigned long int verifyAndMultiply(const std::string& _s)
{
	unsigned long int	nbA = 0;
	unsigned long int	nbB = 0;

	int	startPoint = 0;
	bool isNumberB = false;

	for (int i = 0; i < _s.size() && _s[i] != '('; i++) // Possibly useless since every line analyzed should start by the same prefix : mul(
		startPoint += 1;

	startPoint += 1;

	//std::cout << "START POINT IS " << _s[startPoint] << std::endl;

	//VERIYING IF EXPRESSION IS CORRECT
	for (int i = startPoint; i < _s.size() && _s[i] != ')'; i++)
	{
		if (_s[i] != ',' && (_s[i] < '0' && _s[i] > '9'))
			return (1);
	}

	for (int i = startPoint; i < _s.size() && _s[i] != ')'; i++)
	{
		if (_s[i] == ',' || (_s[i] >= '0' && _s[i] <= '9'))
		{
			if (_s[i] == ',')
			{
				isNumberB = true;
			}
			else if (!isNumberB)
			{
				nbA *= 10;
				nbA += _s[i] - '0';
			}
			else
			{
				nbB *= 10;
				nbB += _s[i] - '0';
			}
		}
		else
			return (1);
	}
	std::cout << "==========" << std::endl;
	std::cout << "Match : " << _s << std::endl;
	std::cout << "Numbers to multiply : " << nbA << " * " << nbB << std::endl;
	std::cout << "Result = " << nbA * nbB << std::endl;
	std::cout << "==========" << std::endl << std::endl;

	return nbA * nbB;
}

void dayThree(const bool& isPartTwo)
{
	FileParser	_file("2024\\InputFiles\\inputD3.txt");
	std::string	line;
	unsigned long long int	finalValue = 0;

	std::regex regex_pattern(R"(mul\(([^a-zA-Z,]+),([^a-zA-Z,]+)\))");

	int		i = 0;

	std::vector<std::string>	lines;

	while ((line = _file.readLineToString()) != "")
	{
		std::string testLine = "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))";

		std::vector<std::string> matches;

		// Utilisation de std::sregex_iterator pour parcourir les occurrences
		auto begin = std::sregex_iterator(line.begin(), line.end(), regex_pattern);
		auto end = std::sregex_iterator();

		for (auto it = begin; it != end; ++it)
		{
			//std::cout << "Full match : " << it->str() << std::endl;
			matches.push_back(it->str()); // Ajout de la correspondance au vecteur
		}

		for (int x = 0; x < matches.size(); x++)
		{
			//std::cout << matches[x] << std::endl;
			finalValue += verifyAndMultiply(matches[x]);
		}
		//std::cout << "FINAL VALUE = " << finalValue << std::endl;
	}

	//while ((line = _file.readLineToString()) != "")
	//{
	//	std::regex_search("mul(20,20)", m, std::regex(re));

	//	for (int i = 0; i < m.size(); i++)
	//	{
	//		//finalValue = finalValue;
	//		std::cout << "Match " << i << ": " << m[i] << std::endl;
	//		finalValue += verifyAndMultiply(m[i]);
	//	}
	//}

	//finalValue = verifyAndMultiply("mul(20,20)");

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}