#include "DayTwo.h"

void initBag(t_bag& _bag)
{
	_bag.red = 12;
	_bag.green = 13;
	_bag.blue = 14;
}

void updateMinimumBag(t_bag& _bag, const int& _quantity, const std::string& _color)
{
	if (_color == "blue," || _color == "blue" || _color == "blue;")
	{
		if (_bag.blue <= _quantity)
			_bag.blue = _quantity;
	}
	else if (_color == "green," || _color == "green" || _color == "green;")
	{
		if (_bag.green <= _quantity)
			_bag.green = _quantity;
	}
	else if (_color == "red," || _color == "red" || _color == "red;")
	{
		if (_bag.red <= _quantity)
			_bag.red = _quantity;
	}
}

void resetMinimumBag(t_bag& _bag)
{
	_bag.blue = 0;
	_bag.green = 0;
	_bag.red = 0;
}

bool checkCubeNumber(const int& _cubes, const std::string& _color, const t_bag& bag)
{
	if ((_color == "blue," || _color == "blue" || _color == "blue;") && _cubes > bag.blue)
		return false;
	else if ((_color == "green," || _color == "green" || _color == "green;") && _cubes > bag.green)
		return false;
	else if ((_color == "red," || _color == "red" || _color == "red;") && _cubes > bag.red)
		return false;
	else
		return true;
}

bool checkIfNumber(const std::string& _word)
{
	for (int i = 0; i < _word.size(); i++)
		if ((_word[i] >= 'a' && _word[i] <= 'z') || (_word[i] >= 'A' && _word[i] <= 'Z'))
			return false;
	return true;
}

int getGameID(const std::string& _string)
{
	int	ret = 0;

	for (int i = 0; _string[i] != ':'; i++)
	{
		if (ret != 0)
			ret *= 10;
		ret += (_string[i] - 48);
	}
	return ret;
}

void dayTwo(const bool& isPartTwo)
{
	FileParser		_fileParser("2023\\InputFiles\\inputD2.txt");
	unsigned int	finalValue = 0;
	std::string		word;
	int				gameID = 0;
	t_bag			bag;
	t_bag			minimumBag;
	int				quantity = 0;
	bool			gameValid = true;

	initBag(bag);

	while ((word = _fileParser.readWordToString()) != "")
	{
		if (word == "Game")
		{
			if (!isPartTwo)
			{
				if (gameValid)
					finalValue += gameID;
			}
			else
			{
				finalValue += (minimumBag.red * minimumBag.green * minimumBag.blue);
			}
			gameID = getGameID(_fileParser.readWordToString());
			std::cout << "GAME ID = " << gameID << std::endl;
			gameValid = true;
			resetMinimumBag(minimumBag);
		}
		else
		{
			if (checkIfNumber(word))
			{
				quantity = std::stoi(word);
				word = _fileParser.readWordToString();
				updateMinimumBag(minimumBag, quantity, word);
				if (!checkCubeNumber(quantity, word, bag))
				{
					std::cout << "NUMBER = " << quantity << " AND COLOR IS " << word << std::endl;
					gameValid = false;
					//continue;
				}
			}
		}
	}

	if (!isPartTwo)
	{
		if (gameValid)
			finalValue += gameID;
	}
	else
	{
		finalValue += (minimumBag.red * minimumBag.green * minimumBag.blue);
	}
	std::cout << finalValue << std::endl;
}
