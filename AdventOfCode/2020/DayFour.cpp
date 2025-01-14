#include "DayFour.h"

bool checkPassport(const std::string& passport, const bool& isPartTwo)
{
	std::vector<std::string>	fields = { "byr:", "iyr:", "eyr:", "hgt:", "hcl:", "ecl:", "pid:", "cid" };

	for (std::string field : fields)
	{
		if (passport.find(field) == std::string::npos && field != "cid")
			return false;
	}

	if (isPartTwo)
	{
		std::istringstream	subFieldStr(passport);
		std::string	subField;
		std::string	rule;

		while ((subField = readWord(subFieldStr)) != "")
		{
			for (std::string field : fields)
				if (subField.find(field) != std::string::npos)
					rule = field;

			if (rule == "byr:")
			{
				subField = subField.substr(4, 4);

				if (std::stoi(subField) < 1920 || std::stoi(subField) > 2002)
					return false;
			}
			else if (rule == "iyr:")
			{
				subField = subField.substr(4, 4);

				if (std::stoi(subField) < 2010 || std::stoi(subField) > 2020)
					return false;
			}
			else if (rule == "eyr:")
			{
				subField = subField.substr(4, 4);

				if (std::stoi(subField) < 2020 || std::stoi(subField) > 2030)
					return false;
			}
			else if (rule == "hgt:")
			{
				if (subField.find("cm") != std::string::npos && subField.find("in") != std::string::npos)
					return false;
				else if (subField.find("cm") != std::string::npos)
				{
					std::string value = subField.substr(4, subField.find("cm") - 4);

					if (std::stoi(value) < 150 || std::stoi(value) > 193)
						return false;
				}
				else if (subField.find("in") != std::string::npos)
				{
					std::string value = subField.substr(4, subField.find("in") - 4);

					unsigned int height = std::stoi(value);

					if (height < 59 || height > 76)
						return false;
				}
				else
					return false;
			}
			else if (rule == "hcl:")
			{
				subField = subField.substr(4, 7);

				if (subField[0] != '#' || subField.size() != 7)
					return false;
				else
				{
					std::string		hexaStr = "0123456789abcdef";
					for (int i = 1; i < subField.size(); i++)
					{
						if (hexaStr.find(subField[i]) == std::string::npos)
							return false;
					}
				}
			}
			else if (rule == "ecl:")
			{
				std::vector<std::string>	ecls = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
				bool						isValidEcl = false;

				subField = subField.substr(4, 3);

				for (std::string ecl : ecls)
				{
					if (ecl == subField)
						isValidEcl = true;
				}
				if (!isValidEcl)
					return false;
			}
			else if (rule == "pid:")
			{
				subField = subField.substr(4);

				if (subField.size() != 9)
					return false;
				for (int i = 0; i < subField.size(); i++)
				{
					if (subField[i] < '0' || subField[i] > '9')
						return false;
				}
			}
		}
	}
	return true;
}

void dayFour(const bool& isPartTwo)
{
	FileParser	_file("2020\\InputFiles\\inputD4.txt");
	std::string	word;
	unsigned long long int	finalValue = 0;

	bool isEndOfFile = false;
	std::string	passport = "";

	while ((word = _file.readLineToString()) != "" || !isEndOfFile)
	{
		if (word != "")
		{
			passport += word;
			passport += ' ';
		}
		else
		{
			if (passport.size() == 0)
				isEndOfFile = true;
			else
			{
				if (checkPassport(passport, isPartTwo))
					finalValue += 1;
				passport.clear();
			}
		}
	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}