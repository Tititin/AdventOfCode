#include "DayOne.h"

void dayOne(const bool& isPartTwo)
{
	FileParser	_fileParser(INPUT_DAY_ONE);
	std::string	line;

	unsigned long long int	finalValue = 0;

	while ((line = _fileParser.readLineToString()) != "")
	{

	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}