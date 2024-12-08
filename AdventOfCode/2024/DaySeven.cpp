#include "DaySeven.h"

void daySeven(const bool& isPartTwo)
{
	FileParser	_file("2024\\InputFiles\\inputD7.txt");
	std::string	line;
	unsigned long long int	finalValue = 0;

	while ((line = _file.readLineToString()) != "")
	{
		unsigned long long int	nb = 0;
		std::vector<unsigned long long int>	operatorNumbers;
		std::vector<unsigned int>			operations;

		unsigned long long int	opNumber = 0;

		for (int i = 0; i < line.size(); i++)
		{
			while (line[i] != ':')
				nb = nb * 10 + (line[i] - '0');

			i += 2;


		}
	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}