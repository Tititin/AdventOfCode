#include "DayThirteen.h"

int getNbDifferentCharacters(const std::string& _s1, const std::string& _s2)
{
	int	nb = 0;

	for (int i = 0; i < _s1.size(); i++)
	{
		if (_s1[i] != _s2[i])
			nb += 1;
	}
	return nb;
}

void dayThirteen(const bool& isPartTwo)
{
	FileParser _fileParser("2023\\InputFiles\\inputD13.txt");
	std::string	line;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int nbOfRetries = 0;

	int	nbCurrentLine = 1;
	int nbLineBelow = 0;
	int	nbLineAbove = 0;

	bool potentialSymetryFound = false;

	std::map<int, bool>	mapsWithSymetryFound;
	std::map<int, bool> mapsPartTwoWithSymetryFound;
	std::map<int, t_RegisteredSymetry> mapsSymetries;

	std::vector<std::vector<std::string>> maps;
	std::vector<std::vector<std::string>> mapsPartTwo;
	std::vector<std::vector<std::string>> mapsDebug;
	std::vector<std::string>	currentMap;

	unsigned long long int finalValue = 0;

	while (nbOfRetries < 2)
	{
		line = _fileParser.readLineToString();
		if (line == "" && nbOfRetries == 0)
		{
			mapsWithSymetryFound.insert(std::pair<int, bool>((int)maps.size(), false));
			maps.push_back(currentMap);
			if (isPartTwo)
			{
				mapsPartTwoWithSymetryFound.insert(std::pair<int, bool>((int)maps.size(), false));
				mapsPartTwo.push_back(currentMap);
			}
			mapsDebug.push_back(currentMap);
			currentMap.clear();
			nbOfRetries += 1;
		}
		else if (line == "")
			nbOfRetries += 1;
		else
		{
			currentMap.push_back(line);
			nbOfRetries = 0;
		}
	}

	//////////////
	// PART ONE //
	//////////////

	// CHECKING HORIZONTAL SYMETRY
	for (int y = 0; y < maps.size(); y++)
	{
		while (!mapsWithSymetryFound[y] && y < maps.size())
		{
			while (nbCurrentLine < maps[y].size() && !potentialSymetryFound)
			{
				if (maps[y][nbCurrentLine] == maps[y][nbCurrentLine - 1])
					potentialSymetryFound = true;
				else
					nbCurrentLine += 1;
			}
			if (potentialSymetryFound)
			{
				nbLineBelow = nbCurrentLine;
				nbLineAbove = nbCurrentLine - 1;

				while (nbLineBelow < maps[y].size() && nbLineAbove >= 0 && potentialSymetryFound)
				{
					if (maps[y][nbLineAbove] != maps[y][nbLineBelow])
						potentialSymetryFound = false;
					else
					{
						nbLineBelow += 1;
						nbLineAbove -= 1;
					}
				}
				if (potentialSymetryFound)
				{
					mapsWithSymetryFound[y] = true;
					mapsSymetries.insert(std::pair<int, t_RegisteredSymetry>(y, t_RegisteredSymetry{ HORIZONTAL, 0, nbCurrentLine, 0 }));
					finalValue += 100 * nbCurrentLine;
					nbLineAbove = 0;
					nbLineBelow = 0;
					nbCurrentLine = 1;
				}
				else if (nbCurrentLine >= maps[y].size() - 1)
				{
					nbCurrentLine = 1;
					nbLineAbove = 0;
					nbLineBelow = 0;
					y += 1;
				}
				else
					nbCurrentLine += 1;
			}
			else
			{
				nbCurrentLine = 1;
				nbLineAbove = 0;
				nbLineBelow = 0;
				y += 1;
			}
		}
	}

	// TRANSPOSING ALL MAPS WITHOUT HORIZONTAL SYMETRY SO WE CAN CONVERT VERTICAL SYMETRY INTO HORIZONTAL SYMETRY
	for (int z = 0; z < maps.size(); z++)
	{
		if (!mapsWithSymetryFound[z])
		{
			std::vector<std::string> tmp = std::vector<std::string>(maps[z][0].size());
			std::string	strtmp;

			for (int y = 0; y < maps[z].size(); y++)
			{
				for (int x = 0; x < maps[z][y].size(); x++)
					tmp[x].push_back(maps[z][y][x]);
			}
			maps[z] = tmp;
		}
	}

	nbCurrentLine = 1;
	potentialSymetryFound = false;

	// LET'S FIND REMAINING HORIZONTAL SYMETRIES ON TRANSPOSED MAPS
	for (int y = 0; y < maps.size(); y++)
	{
		while (!mapsWithSymetryFound[y] && y < maps.size())
		{
			while (nbCurrentLine < maps[y].size() && !potentialSymetryFound)
			{
				if (maps[y][nbCurrentLine] == maps[y][nbCurrentLine - 1])
					potentialSymetryFound = true;
				else
					nbCurrentLine += 1;
			}
			if (potentialSymetryFound)
			{
				nbLineBelow = nbCurrentLine;
				nbLineAbove = nbCurrentLine - 1;
				while (nbLineBelow < maps[y].size() && nbLineAbove >= 0 && potentialSymetryFound)
				{
					if (maps[y][nbLineAbove] != maps[y][nbLineBelow])
						potentialSymetryFound = false;
					else
					{
						nbLineBelow += 1;
						nbLineAbove -= 1;
					}
				}
				if (potentialSymetryFound)
				{
					mapsWithSymetryFound[y] = true;
					finalValue += nbCurrentLine;
					mapsSymetries.insert(std::pair<int, t_RegisteredSymetry>(y, t_RegisteredSymetry{ VERTICAL, 0, 0, nbCurrentLine }));
					nbLineAbove = 0;
					nbLineBelow = 0;
					nbCurrentLine = 1;
				}
				else if (nbCurrentLine >= maps[y].size() - 1)
				{
					nbLineAbove = 0;
					nbLineBelow = 0;
					nbCurrentLine = 1;
					y += 1;
				}
				else
					nbCurrentLine += 1;
			}
			else
			{
				nbLineAbove = 0;
				nbLineBelow = 0;
				nbCurrentLine = 1;
				y += 1;
			}
		}
	}


	//////////////
	// PART TWO //
	//////////////

	if (isPartTwo)
	{
		bool smudgeFound = false;
		nbCurrentLine = 1;
		potentialSymetryFound = false;
		finalValue = 0;

		// CHECKING HORIZONTAL SYMETRY PART TWO
		for (int y = 0; y < mapsPartTwo.size(); y++)
		{
			while (!mapsPartTwoWithSymetryFound[y] && y < mapsPartTwo.size())
			{
				while (nbCurrentLine < mapsPartTwo[y].size() && !potentialSymetryFound)
				{
					if (mapsPartTwo[y][nbCurrentLine] == mapsPartTwo[y][nbCurrentLine - 1] && (nbCurrentLine != mapsSymetries[y].row || mapsSymetries[y].symetry != HORIZONTAL))
						potentialSymetryFound = true;
					else if (getNbDifferentCharacters(mapsPartTwo[y][nbCurrentLine], mapsPartTwo[y][nbCurrentLine - 1]) == 1 && !smudgeFound)
					{
						potentialSymetryFound = true;
						smudgeFound = true;
					}
					else
						nbCurrentLine += 1;
				}
				if (potentialSymetryFound)
				{
					if (!smudgeFound)
					{
						nbLineBelow = nbCurrentLine;
						nbLineAbove = nbCurrentLine - 1;
					}
					else
					{
						nbLineBelow = nbCurrentLine + 1;
						nbLineAbove = nbCurrentLine - 2;
					}

					while (nbLineBelow < mapsPartTwo[y].size() && nbLineAbove >= 0 && potentialSymetryFound)
					{
						if (mapsPartTwo[y][nbLineAbove] != mapsPartTwo[y][nbLineBelow])
						{
							if (!smudgeFound && getNbDifferentCharacters(mapsPartTwo[y][nbLineAbove], mapsPartTwo[y][nbLineBelow]) == 1)
							{
								nbLineBelow += 1;
								nbLineAbove -= 1;
								smudgeFound = true;
							}
							else
								potentialSymetryFound = false;
						}
						else
						{
							nbLineBelow += 1;
							nbLineAbove -= 1;
						}
					}
					if (potentialSymetryFound && smudgeFound)
					{
						mapsPartTwoWithSymetryFound[y] = true;
						mapsSymetries[y].symetry = HORIZONTAL;
						mapsSymetries[y].column = 0;
						mapsSymetries[y].row = nbCurrentLine;
						finalValue += 100 * nbCurrentLine;
						nbLineAbove = 0;
						nbLineBelow = 0;
						nbCurrentLine = 1;
						smudgeFound = false;
						potentialSymetryFound = false;
					}
					else if (nbCurrentLine >= mapsPartTwo[y].size() - 1)
					{
						nbCurrentLine = 1;
						nbLineAbove = 0;
						nbLineBelow = 0;
						y += 1;
						smudgeFound = false;
					}
					else
					{
						nbCurrentLine += 1;
						smudgeFound = false;
					}
				}
				else
				{
					nbCurrentLine = 1;
					nbLineAbove = 0;
					nbLineBelow = 0;
					y += 1;
					smudgeFound = false;
				}
			}
		}

		// TRANSPOSING ALL MAPS WITHOUT HORIZONTAL SYMETRY SO WE CAN CONVERT VERTICAL SYMETRY INTO HORIZONTAL SYMETRY
		for (int z = 0; z < mapsPartTwo.size(); z++)
		{
			if (!mapsPartTwoWithSymetryFound[z])
			{
				std::vector<std::string> tmp = std::vector<std::string>(mapsPartTwo[z][0].size());
				std::string	strtmp;

				for (int y = 0; y < mapsPartTwo[z].size(); y++)
				{
					for (int x = 0; x < mapsPartTwo[z][y].size(); x++)
						tmp[x].push_back(mapsPartTwo[z][y][x]);
				}
				mapsPartTwo[z] = tmp;
			}
		}

		nbCurrentLine = 1;
		potentialSymetryFound = false;
		smudgeFound = false;

		for (int y = 0; y < mapsPartTwo.size(); y++)
		{
			while (!mapsPartTwoWithSymetryFound[y] && y < mapsPartTwo.size())
			{
				while (nbCurrentLine < mapsPartTwo[y].size() && !potentialSymetryFound)
				{
					if (mapsPartTwo[y][nbCurrentLine] == mapsPartTwo[y][nbCurrentLine - 1] && (nbCurrentLine != mapsSymetries[y].column || mapsSymetries[y].symetry != VERTICAL))
						potentialSymetryFound = true;
					else if (getNbDifferentCharacters(mapsPartTwo[y][nbCurrentLine], mapsPartTwo[y][nbCurrentLine - 1]) == 1 && !smudgeFound)
					{
						potentialSymetryFound = true;
						smudgeFound = true;
					}
					else
						nbCurrentLine += 1;
				}
				if (potentialSymetryFound)
				{
					if (!smudgeFound)
					{
						nbLineBelow = nbCurrentLine;
						nbLineAbove = nbCurrentLine - 1;
					}
					else
					{
						nbLineBelow = nbCurrentLine + 1;
						nbLineAbove = nbCurrentLine - 2;
					}

					while (nbLineBelow < mapsPartTwo[y].size() && nbLineAbove >= 0 && potentialSymetryFound)
					{
						if (mapsPartTwo[y][nbLineAbove] != mapsPartTwo[y][nbLineBelow])
						{
							if (!smudgeFound && getNbDifferentCharacters(mapsPartTwo[y][nbLineAbove], mapsPartTwo[y][nbLineBelow]) == 1)
							{
								nbLineBelow += 1;
								nbLineAbove -= 1;
								smudgeFound = true;
							}
							else
								potentialSymetryFound = false;
						}
						else
						{
							nbLineBelow += 1;
							nbLineAbove -= 1;
						}
					}
					if (potentialSymetryFound && smudgeFound)
					{
						mapsPartTwoWithSymetryFound[y] = true;
						mapsSymetries[y].symetry = VERTICAL;
						mapsSymetries[y].column = nbCurrentLine;
						mapsSymetries[y].row = 0;
						finalValue += nbCurrentLine;
						nbLineAbove = 0;
						nbLineBelow = 0;
						nbCurrentLine = 1;
						smudgeFound = false;
						potentialSymetryFound = false;
					}
					else if (nbCurrentLine >= mapsPartTwo[y].size() - 1)
					{
						nbCurrentLine = 1;
						nbLineAbove = 0;
						nbLineBelow = 0;
						y += 1;
						smudgeFound = false;
					}
					else
					{
						nbCurrentLine += 1;
						smudgeFound = false;
					}
				}
				else
				{
					nbCurrentLine = 1;
					nbLineAbove = 0;
					nbLineBelow = 0;
					y += 1;
					smudgeFound = false;
				}
			}
		}
	}

	// DISPLAYING RESULTS

	SetConsoleTextAttribute(hConsole, 8);
	for (int z = 0; z < mapsDebug.size(); z++)
	{
			for (int y = 0; y < mapsDebug[z].size(); y++)
			{
				for (int x = 0; x < mapsDebug[z][y].size(); x++)
				{
					if ((mapsSymetries[z].symetry == HORIZONTAL && (y == mapsSymetries[z].row || y == mapsSymetries[z].row - 1))
						|| (mapsSymetries[z].symetry == VERTICAL && (x == mapsSymetries[z].column || x == mapsSymetries[z].column - 1)))
						SetConsoleTextAttribute(hConsole, 10);
					else
						SetConsoleTextAttribute(hConsole, 8);
					std::cout << mapsDebug[z][y][x];
				}
				std::cout << std::endl;
			}
			SetConsoleTextAttribute(hConsole, 8);
			if (mapsSymetries[z].symetry == HORIZONTAL)
				std::cout << "VALUE = " << mapsSymetries[z].row * 100 << std::endl;
			else
				std::cout << "VALUE = " << mapsSymetries[z].column << std::endl;
			std::cout << std::endl;
	}
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << "FINAL VALUE = " << finalValue << std::endl;
	SetConsoleTextAttribute(hConsole, 8);
}
