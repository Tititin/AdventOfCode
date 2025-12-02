#include "DayTwo.h"

void dayTwo(const bool& isPartTwo)
{
	FileParser	_fileParser("2025//InputFiles//inputD2.txt");
	std::string	line;
	std::string	word;

	size_t		posA = 0;
	size_t		posB = 0;
	size_t		dashPos = 0;

	unsigned long long int	startNb = 0;
	unsigned long long int	endNb = 0;

	unsigned long long int	finalValue = 0;

	line = _fileParser.readLineToString();

	while (posA != std::string::npos)
	{
		posB = line.find(',', posA);
		word = line.substr(posA, posB - posA);
		dashPos = word.find('-');

		startNb = std::stoull(word.substr(0, dashPos));
		endNb = std::stoull(word.substr(dashPos + 1));

		for (unsigned long long int n = startNb; n <= endNb; n++)
		{
			std::string		nbStr = std::to_string(n);

			if (isPartTwo)
			{
				size_t	patternLength = 1;
				bool	invalidID = false;
				bool	repeatedPattern = true;

				while (!invalidID && patternLength <= nbStr.size() / 2)
				{
					repeatedPattern = true;
					for (int i = 0; i < nbStr.size() - patternLength && repeatedPattern; i += patternLength)
					{
						std::string	strA = nbStr.substr(i, patternLength);
						std::string strB = nbStr.substr(i + patternLength, patternLength);

						if (strA == strB)
							repeatedPattern = true;
						else
							repeatedPattern = false;

					}
					if (repeatedPattern)
						invalidID = true;
					else
						patternLength += 1;
				}
				if (invalidID)
					finalValue += n;
			}
			else
			{
				if (nbStr.substr(0, nbStr.size() / 2) == nbStr.substr(nbStr.size() / 2))
					finalValue += n;
			}
		}

		if (posB == std::string::npos)
			posA = std::string::npos;
		else
			posA = posB + 1;
	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}
