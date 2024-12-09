#include "DayThree.h"

void cleanZonesVectors(std::vector<std::size_t>& doTriggers, std::vector<std::size_t>& dontTriggers)
{
	std::vector<char>	safeOrUnsafe;
	int	x = 0;
	int y = 0;

	while (x < doTriggers.size() && y < dontTriggers.size())
	{
		if (doTriggers[x] < dontTriggers[y])
		{
			safeOrUnsafe.push_back('s');
			x += 1;
		}
		else if (doTriggers[x] > dontTriggers[y])
		{
			safeOrUnsafe.push_back('u');
			y += 1;
		}
	}
	while (x++ < doTriggers.size())
		safeOrUnsafe.push_back('s');
	while (y++ < dontTriggers.size())
		safeOrUnsafe.push_back('u');

	x = 1;
	y = 0;

	for (int i = 1; i < safeOrUnsafe.size(); i++)
	{
		if (safeOrUnsafe[i] == safeOrUnsafe[i - 1])
		{
			if (safeOrUnsafe[i] == 's')
				doTriggers.erase(doTriggers.begin() + x);
			else
				dontTriggers.erase(dontTriggers.begin() + y);
		}
		else if (safeOrUnsafe[i] == 's')
			x += 1;
		else
			y += 1;
	}
}

bool checkIfInSafeZone(const size_t& pos, const std::vector<t_SafeZones>& safeZones)
{
	bool	safeZoneFound = false;

	for (int i = 0; i < safeZones.size() && !safeZoneFound; i++)
	{
		if (pos > safeZones[i].start && pos < safeZones[i].end)
			safeZoneFound = true;
	}

	return safeZoneFound;
}

std::string checkIfMulExpression(int pos, const std::string& str)
{
	bool	isMul = true;
	bool	isExpressionCorrect = false;
	bool	firstNumberFound = false;
	bool	commaFound = false;
	bool	secondNumberFound = false;
	bool	closingParenthesisFound = false;

	std::size_t	expressionLength = 0;
	//std::string	pattern = "mul(";

	//std::cout << "ANALYZING MATCH AT POS -> " << pos << std::endl;
	//std::cout << str.substr(pos, 4);

	for (int i = pos + 4; i < str.size() && isMul && !isExpressionCorrect; i++)
	{
		//std::cout << str[i];
		if (!firstNumberFound && (str[i] < '0' || str[i] > '9') && str[i] != ',')
		{
			//std::cout << std::endl;
			//std::cout << "Error on first number" << std::endl;
			isMul = false;
		}
		else if (!firstNumberFound && str[i] == ',')
		{
			firstNumberFound = true;
			commaFound = true;
		}
		else if (commaFound && str[i] == ',')
		{
			//std::cout << std::endl;
			//std::cout << "Double-comma error" << std::endl;
			isMul = false;
		}
		else if (firstNumberFound && commaFound && !secondNumberFound && (str[i] < '0' || str[i] > '9') && str[i] != ')')
		{
			/*std::cout << std::endl;
			std::cout << "Error on second number" << std::endl;*/
			isMul = false;
		}
		else if (firstNumberFound && commaFound && !secondNumberFound && str[i] == ')')
		{
			secondNumberFound = true;
			closingParenthesisFound = true;
			isExpressionCorrect = true;
			expressionLength = i - pos;
		}
		//else
		//{
		//	std::cout << std::endl;
		//	std::cout << "Wrong expression" << std::endl;
		//	isMul = false;
		//}
		//continue;
	}

	if (isMul && isExpressionCorrect)
		return (str.substr(pos, expressionLength + 1));

	return std::string("ERROR");
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
	/*std::cout << "==========" << std::endl;
	std::cout << "Match : " << _s << std::endl;
	std::cout << "Numbers to multiply : " << nbA << " * " << nbB << std::endl;
	std::cout << "Result = " << nbA * nbB << std::endl;
	std::cout << "==========" << std::endl << std::endl;*/

	return nbA * nbB;
}

void dayThree(const bool& isPartTwo)
{
	FileParser	_file("2024\\InputFiles\\inputD3bis.txt");
	std::string	line;
	unsigned long long int	finalValue = 0;

	//std::regex regex_pattern(R"(mul\(([^a-zA-Z,]+),([^a-zA-Z,]+)\))");

	/*int		i = 0;*/

	/*std::vector<std::string>	lines;*/

	//while ((line = _file.readLineToString()) != "")
	//{
	//	//std::string testLine = "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))";

	//	//std::vector<std::string> matches;

	//	// Utilisation de std::sregex_iterator pour parcourir les occurrences
	//	//auto begin = std::sregex_iterator(line.begin(), line.end(), regex_pattern);
	//	//auto end = std::sregex_iterator();

	//	//for (auto it = begin; it != end; ++it)
	//	//{
	//	//	//std::cout << "Full match : " << it->str() << std::endl;
	//	//	matches.push_back(it->str()); // Ajout de la correspondance au vecteur
	//	//}

	//	//for (int x = 0; x < matches.size(); x++)
	//	//{
	//	//	//std::cout << matches[x] << std::endl;
	//	//	finalValue += verifyAndMultiply(matches[x]);
	//	//}
	//	//std::cout << "FINAL VALUE = " << finalValue << std::endl;
	//}

	std::size_t matchPos = 0;
	std::size_t doMatchPos = 0;
	std::size_t dontMatchPos = 0;

	bool		isMulActivated = true;

	std::vector<t_SafeZones>	safeZones;
	std::vector<std::size_t>			doTriggers;
	std::vector<std::size_t>			dontTriggers;

	doTriggers.push_back(0);

	while ((line = _file.readLineToString()) != "")
	{
		while ((doMatchPos = line.find("do()", doMatchPos)) != std::string::npos)
		{
			doTriggers.push_back(doMatchPos);
			doMatchPos += 1;
		}
		while ((dontMatchPos = line.find("don't()", dontMatchPos)) != std::string::npos)
		{
			dontTriggers.push_back(dontMatchPos);
			dontMatchPos += 1;
		}

		cleanZonesVectors(doTriggers, dontTriggers);

		std::cout << "START OF SAFE ZONES" << std::endl;
		for (int i = 0; i < doTriggers.size(); i++)
			std::cout << doTriggers[i] << " ";
		std::cout << std::endl;
		std::cout << "END OF SAFE ZONES" << std::endl;
		for (int i = 0; i < dontTriggers.size(); i++)
			std::cout << dontTriggers[i] << " ";
		std::cout << std::endl << std::endl;

		for (int i = 0; i < doTriggers.size() && i < dontTriggers.size(); i++)
			safeZones.push_back(t_SafeZones{ doTriggers[i], dontTriggers[i] });
		if (doTriggers.size() > dontTriggers.size())
			safeZones.push_back(t_SafeZones{ doTriggers.size() - 1, std::string::npos });
		else if (dontTriggers.size() > doTriggers.size())
			safeZones.push_back(t_SafeZones{ std::string::npos, dontTriggers.size() - 1 });

		while ((matchPos = line.find("mul(", matchPos)) != std::string::npos)
		{
			std::string	potentialMatch = checkIfMulExpression(matchPos, line);

			//std::cout << "Match : " << potentialMatch << std::endl;

			if (potentialMatch != "ERROR" && checkIfInSafeZone(matchPos, safeZones))
				finalValue += verifyAndMultiply(potentialMatch);

			matchPos += 1;
		}
		matchPos = 0;
		doMatchPos = 0;
		dontMatchPos = 0;
		safeZones.clear();
		doTriggers.clear();
		dontTriggers.clear();
		//doTriggers.push_back(0);
	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}