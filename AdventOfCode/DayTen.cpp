#include "DayTen.h"

bool isSpriteVisible(int cycle, int spritePos)
{
	if (spritePos == cycle
		|| spritePos - 1 == cycle
		|| spritePos + 1 == cycle)
		return (true);
	return (false);
}

void dayTen(bool isPartTwo)
{
	FileParser fileParser("..\\inputD10.txt");
	int nbCycles = 0;
	int nbSteps = 0;

	std::string move;
	int value = 1;

	bool isCmd = true;

	int outputRes = 0;
	int finalOutput = 0;

	// PART TWO
	std::string cycleLine = "";

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	while ((move = fileParser.readMove()) != "")
	{
		if (isCmd)
		{
			if (move == "noop")
			{
				if (isSpriteVisible(nbCycles % 40, value))
					cycleLine.push_back('#');
				else
					cycleLine.push_back('.');
				nbCycles += 1;
			}
			else
			{
				if (isSpriteVisible(nbCycles % 40, value))
					cycleLine.push_back('#');
				else
					cycleLine.push_back('.');
				nbCycles += 1;
				if (isSpriteVisible(nbCycles % 40, value))
					cycleLine.push_back('#');
				else
					cycleLine.push_back('.');
				nbCycles += 1;
				isCmd = !isCmd;
			}

			if (!isPartTwo)
			{
				if (nbCycles >= 20 && nbCycles <= 21 && nbSteps == 0)
				{
					outputRes = 20 * value;
					std::cout << "VALUE AFTER 20TH CYCLE = " << outputRes << std::endl;
					nbSteps += 1;
					finalOutput += outputRes;
				}
				else if (nbCycles >= 60 && nbCycles <= 61 && nbSteps == 1)
				{
					outputRes = 60 * value;
					std::cout << "VALUE AFTER 60TH CYCLE = " << outputRes << std::endl;
					nbSteps += 1;
					finalOutput += outputRes;
				}
				else if (nbCycles >= 100 && nbCycles <= 101 && nbSteps == 2)
				{
					outputRes = 100 * value;
					std::cout << "VALUE AFTER 100TH CYCLE = " << outputRes << std::endl;
					nbSteps += 1;
					finalOutput += outputRes;
				}
				else if (nbCycles >= 140 && nbCycles <= 141 && nbSteps == 3)
				{
					outputRes = 140 * value;
					std::cout << "VALUE AFTER 140TH CYCLE = " << outputRes << std::endl;
					nbSteps += 1;
					finalOutput += outputRes;
				}
				else if (nbCycles >= 180 && nbCycles <= 181 && nbSteps == 4)
				{
					outputRes = 180 * value;
					std::cout << "VALUE AFTER 180TH CYCLE = " << outputRes << std::endl;
					nbSteps += 1;
					finalOutput += outputRes;
				}
				else if (nbCycles >= 220 && nbCycles <= 221 && nbSteps == 5)
				{
					outputRes = 220 * value;
					std::cout << "VALUE AFTER 220TH CYCLE = " << outputRes << std::endl;
					nbSteps += 1;
					finalOutput += outputRes;
				}
			}
		}
		else
		{
			value += std::stoi(move);
			isCmd = !isCmd;
		}
	}

	if (!isPartTwo)
		std::cout << "FINAL OUTPUT : " << finalOutput << std::endl;
	else
	{
		for (int i = 0; i < cycleLine.size(); i++)
		{
			if (i % 40 == 0 && i / 40 > 0)
				std::cout << std::endl;
			if (cycleLine[i] == '#')
			{
				SetConsoleTextAttribute(hConsole, 10);
				std::cout << cycleLine[i];
				SetConsoleTextAttribute(hConsole, 15);
			}
			else
			{
				SetConsoleTextAttribute(hConsole, 12);
				std::cout << cycleLine[i];
				SetConsoleTextAttribute(hConsole, 15);
			}
		}
	}
}
