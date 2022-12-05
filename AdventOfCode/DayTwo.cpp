#include "DayTwo.h"

int		calcWin(const std::string& opponentMove, const std::string& playerMove)
{
	if (opponentMove == "A" && playerMove == "Y"
		|| opponentMove == "B" && playerMove == "Z"
		|| opponentMove == "C" && playerMove == "X")
		return (6);
	else
		return (0);
}

int		calcDraw(const std::string& opponentMove, const std::string& playerMove)
{
	if (opponentMove == "A" && playerMove == "X"
		|| opponentMove == "B" && playerMove == "Y"
		|| opponentMove == "C" && playerMove == "Z")
		return (3);
	else
		return (0);
}

int		calcScore(const std::string& opponentMove, const std::string& playerMove, bool isPartTwo)
{
	int moveScore = 0;

	if (!isPartTwo)
	{
		moveScore = 1 + playerMove[0] - 'X';

		return (moveScore + calcWin(opponentMove, playerMove) + calcDraw(opponentMove, playerMove));
	}
	else
	{
		std::string tempMove = playerMove;
		if (playerMove == "X")
			tempMove[0] = 'X' + ((opponentMove[0] - 'A' + 2) % 3);
		else if (playerMove == "Y")
			tempMove[0] = 'X' + (opponentMove[0] - 'A');
		else
			tempMove[0] = 'X' + ((opponentMove[0] - 'A' + 1) % 3);

		moveScore = 1 + tempMove[0] - 'X';

		return (moveScore + calcWin(opponentMove, tempMove) + calcDraw(opponentMove, tempMove));
	}
}

void	dayTwo()
{
	FileParser fileParser("..\\inputD2.txt");
	std::string playerMove;
	std::string opponentMove;

	std::string move;
	bool isOpponentMove = true;

	int score = 0;

	while ((move = fileParser.readMove()) != "")
	{
		if (isOpponentMove)
			opponentMove = move;
		else
		{
			playerMove = move;
			score += calcScore(opponentMove, playerMove, true);
		}
		isOpponentMove = !isOpponentMove;
	}

	std::cout << score << std::endl;
}