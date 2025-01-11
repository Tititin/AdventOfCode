#include "DayThirteen.h"

bool checkEndGame(const t_GameParam& _params)
{
	if (_params.buttonA.moveX * _params.buttonPress.pressA + _params.buttonB.moveX * _params.buttonPress.pressB == _params.goalPosX
		&& _params.buttonA.moveY * _params.buttonPress.pressA + _params.buttonB.moveY * _params.buttonPress.pressB == _params.goalPosY)
		return true;
	return false;
}

bool playGame(t_GameParam& params)
{
	bool	isGameCleared = false;

	std::cout << "PLAYING GAME WITH FOLLOWING PARAMETERS" << std::endl;
	std::cout << "GOAL POSITION : " << params.goalPosX << ";" << params.goalPosY << std::endl;
	std::cout << "BUTTON A MOVES : " << params.buttonA.moveX << ";" << params.buttonA.moveY << std::endl;
	std::cout << "BUTTON B MOVES : " << params.buttonB.moveX << ";" << params.buttonB.moveY << std::endl;
	std::cout << "==============================" << std::endl;

	for (int i = 0; i < 100 && !(isGameCleared = checkEndGame(params)); i++)
	{
		params.buttonPress.pressA = i;
		for (int j = 0; j < 100 && !(isGameCleared = checkEndGame(params)); j++)
			params.buttonPress.pressB = j;
	}

	std::cout << "GAME ENDED -> " << isGameCleared << " WITH SCORE (A;B) = " << params.buttonPress.pressA << ";" << params.buttonPress.pressB << std::endl;
	std::cout << std::endl;

	return isGameCleared;
}

bool playGamePartTwo(t_GameParam& params)
{
	std::vector<std::vector<long long int>>	matrix(2, std::vector<long long int>(2));
	std::vector<unsigned long long int>					constantMatrix(2);

	long double	det;

	//params.goalPosX += 10000000000000;
	//params.goalPosY += 10000000000000;

	matrix[0][0] = params.buttonA.moveX;
	matrix[0][1] = params.buttonB.moveX;
	matrix[1][0] = params.buttonA.moveY;
	matrix[1][1] = params.buttonB.moveY;
	
	det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

	std::cout << "============" << std::endl;
	std::cout << "MATRIX" << std::endl;
	std::cout << matrix[0][0] << " | " << matrix[0][1] << std::endl;
	std::cout << matrix[1][0] << " | " << matrix[1][1] << std::endl;
	std::cout << "DET = " << matrix[0][0] * matrix[1][1] << " - " << matrix[0][1] * matrix[1][0] << std::endl;

	long long int	tmpA = params.buttonB.moveX;
	long long int	tmpB = params.buttonA.moveY;

	matrix[0][0] = params.buttonB.moveY;
	matrix[0][1] = tmpA * -1;
	matrix[1][0] = tmpB * -1;
	matrix[1][1] = params.buttonA.moveX;


	constantMatrix[0] = params.goalPosX;
	constantMatrix[1] = params.goalPosY;


	std::cout << "DET = " << det << std::endl;
	std::cout << "CONSTANTS = " << constantMatrix[0] << ";" << constantMatrix[1] << std::endl;

	if (det <= 0.0f)
		return false;

	//std::cout << "OK" << std::endl;

	std::cout << "----" << std::endl;
	std::cout << "NEW MATRIX" << std::endl;
	std::cout << matrix[0][0] << " | " << matrix[0][1] << std::endl;
	std::cout << matrix[1][0] << " | " << matrix[1][1] << std::endl;

	std::cout << (matrix[0][0] * constantMatrix[0] + matrix[0][1] * constantMatrix[1]) << std::endl;
	std::cout << (matrix[1][0] * constantMatrix[0] + matrix[1][1] * constantMatrix[1]) << std::endl;

	params.buttonPress.pressA = (double)(matrix[0][0] * constantMatrix[0] + matrix[0][1] * constantMatrix[1]) / det;
	params.buttonPress.pressB = (double)(matrix[1][0] * constantMatrix[0] + matrix[1][1] * constantMatrix[1]) / det;

	std::cout << "SOLUTION IS (A;B) " << params.buttonPress.pressA << ";" << params.buttonPress.pressB << std::endl;

	return true;
}

void dayThirteen(const bool& isPartTwo)
{
	FileParser	_file("2024\\InputFiles\\inputD13bis.txt");
	std::string	word;
	unsigned long long int	finalValue = 0;

	t_GameParam		gameParam;
	//t_ButtonPress	buttonPress;

	bool	isAnalyzedButtonA = false;

	while ((word = _file.readWordToString()) != "")
	{
		//std::cout << word << std::endl;
		if (word.find("Button") != std::string::npos)
		{
			for (int i = 0; i < 2; i++)
				word = _file.readWordToString();

			if (!isAnalyzedButtonA)
				gameParam.buttonA.moveX = std::stoi(word.substr(2, word.size() - 3));
			else
				gameParam.buttonB.moveX = std::stoi(word.substr(2, word.size() - 3));

			word = _file.readWordToString();

			if (!isAnalyzedButtonA)
				gameParam.buttonA.moveY = std::stoi(word.substr(2));
			else
				gameParam.buttonB.moveY = std::stoi(word.substr(2));

			isAnalyzedButtonA = !isAnalyzedButtonA;
		}
		else if (word.find("Prize") != std::string::npos)
		{
			word = _file.readWordToString();

			gameParam.goalPosX = std::stoi(word.substr(2, word.size() - 3));

			word = _file.readWordToString();

			gameParam.goalPosY = std::stoi(word.substr(2));

			if (playGamePartTwo(gameParam))
				finalValue += (gameParam.buttonPress.pressA * 3 + gameParam.buttonPress.pressB);
		}

	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}
