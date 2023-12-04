#include "DayFour.h"

int calculateMatches(std::vector<std::string>& _winNbs, std::vector<std::string>& _playerNbs)
{
	int retVal = 0;

	for (int i = 0; i < _winNbs.size(); i++)
	{
		for (int j = 0; j < _playerNbs.size(); j++)
		{
			if (_winNbs[i] == _playerNbs[j])
			{
				if (retVal == 0)
					retVal = 1;
				else
					retVal *= 2;
			}
		}
	}
	return retVal;
}

void calculateMatchesPartTwo(unsigned int& finalValue, std::vector<t_Card>& _cards, std::vector<int>& _quantity)
{
	int	nextCardToAdd;
	int	cardIndex = 1;

	int totalCards = 0;

	static int i = 0;
	int j = 0;

	nextCardToAdd = cardIndex + 1;

	while (cardIndex < _cards.size())
	{
		int retVal = 0;

		while (_quantity[cardIndex] > 0)
		{
			while (i < _cards[cardIndex]._winNbs.size())
			{
				while (j < _cards[cardIndex]._playerNbs.size())
				{
					if (_cards[cardIndex]._winNbs[i] == _cards[cardIndex]._playerNbs[j])
					{
						if (nextCardToAdd < _cards.size())
						{
							_quantity[nextCardToAdd] += 1;
							nextCardToAdd += 1;
						}
					}
					j += 1;
				}
				i += 1;
				j = 0;
			}
			i = 0;
			_quantity[cardIndex] -= 1;
			finalValue += 1;
			nextCardToAdd = cardIndex + 1;
		}
		cardIndex += 1;
		nextCardToAdd = cardIndex + 1;
	}
}

void dayFour(const bool& isPartTwo)
{
	FileParser	_fileParser("2023\\InputFiles\\inputD4.txt");

	unsigned int	finalValue = 0;
	std::string		word;
	bool			isFillingWinner = true;

	//PART TWO
	t_Card						tmp;
	std::vector<t_Card>			cards;
	std::vector<int>			cardQuantities;

	while ((word = _fileParser.readWordToString()) != "")
	{
		if (word.find(':') == std::string::npos && word.find('C') == std::string::npos && word.find('|') == std::string::npos)
		{
			if (word != "|")
			{
				if (isFillingWinner)
					tmp._winNbs.push_back(word);
				else
					tmp._playerNbs.push_back(word);
			}
		}
		else
		{
			if (word == "|")
				isFillingWinner = false;
			else if (word[word.size() - 1] == ':')
			{
				word.pop_back();
				tmp._id = std::stoi(word);
			}
			else if (word == "Card")
			{
				isFillingWinner = true;
				cards.push_back(tmp);
				cardQuantities.push_back(1);
				tmp._playerNbs.clear();
				tmp._winNbs.clear();
			}
		}
	}

	cards.push_back(tmp);
	cardQuantities.push_back(1);
	tmp._playerNbs.clear();
	tmp._winNbs.clear();

	if (!isPartTwo)
	{
		for (int i = 0; i < cards.size(); i++)
		{
			finalValue += calculateMatches(cards[i]._winNbs, cards[i]._playerNbs);
		}
	}
	else
		calculateMatchesPartTwo(finalValue, cards, cardQuantities);

	std::cout << finalValue << std::endl;
}
