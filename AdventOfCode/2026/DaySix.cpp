#include "DaySix.h"

void daySix(const bool& isPartTwo)
{
	FileParser	_fileParser(INPUT_DAY_SIX);
	std::string	line;

	unsigned long long int	finalValue = 0;

	while ((line = _fileParser.readLineToString()) != "")
	{

	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}