#include "DayOne.h"

bool verifyPosition(const t_Pos& _pos, const std::vector<t_Pos>& _visitedPos)
{
	bool	doublePosFound = false;

	for (int i = 0; i < _visitedPos.size() && !doublePosFound; i++)
	{
		if (_visitedPos[i].x == _pos.x
			&& _visitedPos[i].y == _pos.y)
			doublePosFound = true;
	}
	return doublePosFound;
}

void dayOne(const bool& isPartTwo)
{
	FileParser		_file("2016\\InputFiles\\inputD1.txt");
	std::string		word;
	unsigned int	finalValue = 0;

	t_Pos			currentPos = t_Pos{ 0, 0 };
	t_Direction		currentDirection = UP;

	std::vector<t_Pos>	visitedPos;
	bool				foundHQ = false;

	visitedPos.push_back(currentPos);
	while ((word = _file.readWordToString()) != "" && !foundHQ)
	{
		int	nbSteps = 0;

		for (int i = 1; i < word.size() && word[i] != ','; i++)
		{
			nbSteps *= 10;
			nbSteps += word[i] - '0';
		}

		if (word[0] == 'L')
		{
			switch (currentDirection)
			{
			case UP:
				for (int i = 0; i < nbSteps && !foundHQ; i++)
				{
					currentPos.x -= 1;
					if (isPartTwo && !verifyPosition(currentPos, visitedPos))
						visitedPos.push_back(currentPos);
					else if (isPartTwo)
						foundHQ = true;
				}
				currentDirection = LEFT;
				break;

			case DOWN:
				for (int i = 0; i < nbSteps && !foundHQ; i++)
				{
					currentPos.x += 1;
					if (isPartTwo && !verifyPosition(currentPos, visitedPos))
						visitedPos.push_back(currentPos);
					else if (isPartTwo)
						foundHQ = true;
				}
				currentDirection = RIGHT;
				break;

			case LEFT:
				for (int i = 0; i < nbSteps && !foundHQ; i++)
				{
					currentPos.y += 1;
					if (isPartTwo && !verifyPosition(currentPos, visitedPos))
						visitedPos.push_back(currentPos);
					else if (isPartTwo)
						foundHQ = true;
				}
				currentDirection = DOWN;
				break;

			case RIGHT:
				for (int i = 0; i < nbSteps && !foundHQ; i++)
				{
					currentPos.y -= 1;
					if (isPartTwo && !verifyPosition(currentPos, visitedPos))
						visitedPos.push_back(currentPos);
					else if (isPartTwo)
						foundHQ = true;
				}
				currentDirection = UP;
				break;
			}
		}
		else if (word[0] == 'R')
		{
			switch (currentDirection)
			{
			case UP:
				for (int i = 0; i < nbSteps && !foundHQ; i++)
				{
					currentPos.x += 1;
					if (isPartTwo && !verifyPosition(currentPos, visitedPos))
						visitedPos.push_back(currentPos);
					else if (isPartTwo)
						foundHQ = true;
				}
				currentDirection = RIGHT;
				break;

			case DOWN:
				for (int i = 0; i < nbSteps && !foundHQ; i++)
				{
					currentPos.x -= 1;
					if (isPartTwo && !verifyPosition(currentPos, visitedPos))
						visitedPos.push_back(currentPos);
					else if (isPartTwo)
						foundHQ = true;
				}
				currentDirection = LEFT;
				break;

			case LEFT:
				for (int i = 0; i < nbSteps && !foundHQ; i++)
				{
					currentPos.y -= 1;
					if (isPartTwo && !verifyPosition(currentPos, visitedPos))
						visitedPos.push_back(currentPos);
					else if (isPartTwo)
						foundHQ = true;
				}
				currentDirection = UP;
				break;

			case RIGHT:
				for (int i = 0; i < nbSteps && !foundHQ; i++)
				{
					currentPos.y += 1;
					if (isPartTwo && !verifyPosition(currentPos, visitedPos))
						visitedPos.push_back(currentPos);
					else if (isPartTwo)
						foundHQ = true;
				}
				currentDirection = DOWN;
				break;
			}
		}
	}

	finalValue = abs(currentPos.x) + abs(currentPos.y);

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}