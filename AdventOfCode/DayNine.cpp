#include "DayNine.h"

t_Pos calcTranslationVector(const t_Pos& start, const t_Pos& end)
{
	t_Pos vector = { end.x - start.x, end.y - start.y };

	return (vector);
}

void checkAndAddPosition(std::list<t_Pos>& visitedPos, t_Pos pos)
{
	for (std::list<t_Pos>::iterator it = visitedPos.begin(); it != visitedPos.end(); it++)
	{
		if (it->x == pos.x && it->y == pos.y)
			return;
	}
	visitedPos.push_back(pos);
}

void moveHead(std::list<t_Pos>& visitedPos, t_Pos& headPos, t_Pos& tailPos, const std::string& direction, const int& length)
{
	int remain = length;
	t_Pos savedHeadPos = headPos;

	while (remain > 0)
	{
		if (direction == "L")
			headPos.x -= 1;
		else if (direction == "R")
			headPos.x += 1;
		else if (direction == "U")
			headPos.y -= 1;
		else
			headPos.y += 1;

		if (headPos.x - tailPos.x > 1
			|| headPos.x - tailPos.x < -1
			|| headPos.y - tailPos.y > 1
			|| headPos.y - tailPos.y < -1)
			tailPos = savedHeadPos;

		checkAndAddPosition(visitedPos, tailPos);
		savedHeadPos = headPos;
		remain -= 1;
	}
}

void moveHead(std::list<t_Pos>& visitedPos, t_Pos ropePos[], const std::string& direction, const int& length)
{
	int remain = length;
	t_Pos savedHeadPos = ropePos[0];
	t_Pos translationVector = { 0,0 };

	while (remain > 0)
	{
		if (direction == "L")
			ropePos[0].x -= 1;
		else if (direction == "R")
			ropePos[0].x += 1;
		else if (direction == "U")
			ropePos[0].y -= 1;
		else
			ropePos[0].y += 1;

		if (ropePos[0].x - ropePos[1].x > 1
			|| ropePos[0].x - ropePos[1].x < -1
			|| ropePos[0].y - ropePos[1].y > 1
			|| ropePos[0].y - ropePos[1].y < -1)
		{
			for (int i = 1; i < 10; i++)
			{
				if (ropePos[i - 1].x - ropePos[i].x > 1
					|| ropePos[i - 1].x - ropePos[i].x < -1
					|| ropePos[i - 1].y - ropePos[i].y > 1
					|| ropePos[i - 1].y - ropePos[i].y < -1)
				{
					translationVector = calcTranslationVector(ropePos[i], ropePos[i - 1]);
					if (translationVector.x > 1 || translationVector.x < -1)
						translationVector.x /= 2;
					if (translationVector.y > 1 || translationVector.y < -1)
						translationVector.y /= 2;
					ropePos[i].x += translationVector.x;
					ropePos[i].y += translationVector.y;
				}
			}
		}
		checkAndAddPosition(visitedPos, ropePos[9]);
		remain -= 1;
	}
}

void dayNine(bool isPartTwo)
{
	FileParser			fileParser("..\\inputD9.txt");
	std::list<t_Pos>	visitedPos;
	t_Pos				tailPos = { 0, 0 };
	t_Pos				headPos = { 0, 0 };

	t_Pos				ropePos[10] = { 0,0 };

	int x = 0;
	int y = 0;

	std::string move;
	std::string direction;
	int length;
	bool isDirectionMove = true;

	visitedPos.push_back(tailPos);

	while ((move = fileParser.readMove()) != "")
	{
		if (isDirectionMove)
			direction = move;
		else
		{
			length = std::stoi(move);
			if (!isPartTwo)
				moveHead(visitedPos, headPos, tailPos, direction, length);
			else
				moveHead(visitedPos, ropePos, direction, length);
		}
		isDirectionMove = !isDirectionMove;
	}

	std::cout << visitedPos.size() << std::endl;
}
