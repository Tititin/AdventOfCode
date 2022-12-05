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

int		calcScore(const std::string& opponentMove, const std::string& playerMove)
{
	int moveScore = 1 + playerMove[0] - 'X';

	return (moveScore + calcWin(opponentMove, playerMove) + calcDraw(opponentMove, playerMove));
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
			score += calcScore(opponentMove, playerMove);
		}
		isOpponentMove = !isOpponentMove;
	}

	std::cout << score << std::endl;
}