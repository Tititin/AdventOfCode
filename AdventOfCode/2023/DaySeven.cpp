#include "DaySeven.h"

void initCardValues(std::vector<char>& _cards, const bool& isPartTwo)
{
	if (!isPartTwo)
	{
		_cards.push_back('2');
		_cards.push_back('3');
		_cards.push_back('4');
		_cards.push_back('5');
		_cards.push_back('6');
		_cards.push_back('7');
		_cards.push_back('8');
		_cards.push_back('9');
		_cards.push_back('T');
		_cards.push_back('J');
		_cards.push_back('Q');
		_cards.push_back('K');
		_cards.push_back('A');
	}
	else
	{
		_cards.push_back('J');
		_cards.push_back('2');
		_cards.push_back('3');
		_cards.push_back('4');
		_cards.push_back('5');
		_cards.push_back('6');
		_cards.push_back('7');
		_cards.push_back('8');
		_cards.push_back('9');
		_cards.push_back('T');
		_cards.push_back('Q');
		_cards.push_back('K');
		_cards.push_back('A');
	}
}

bool checkFiveOfHands(const std::string& _hand, const bool& isPartTwo)
{
	char c = _hand[0];

	if (isPartTwo && c == 'J')
	{
		for (int i = 0; i < _hand.size(); i++)
		{
			if (_hand[i] != 'J')
				c = _hand[i];
		}
	}
	for (int i = 1; i < _hand.size(); i++)
	{
		if (_hand[i] != c)
		{
			if (!isPartTwo || (isPartTwo && _hand[i] != 'J'))
				return false;
		}
	}
	return true;
}

bool checkFourOfHands(const std::string& _hand, const std::vector<char>& _cards, const bool& isPartTwo)
{
	int nb = 0;

	for (int x = 0; x < _cards.size(); x++)
	{
		for (int y = 0; y < _hand.size(); y++)
		{
			if (_hand[y] == _cards[x] || (isPartTwo && _hand[y] == 'J'))
				nb += 1;
		}
		if (nb == 4)
			return true;
		else
			nb = 0;
	}
	return false;
}

bool checkFullHouseHands(const std::string& _hand, const std::vector<char>& _cards, const bool& isPartTwo)
{
	std::vector<char>	characters;
	bool				isCharExist = false;

	int nbCharDifferent = 1;

	if (!isPartTwo || (isPartTwo && _hand[0] != 'J'))
		characters.push_back(_hand[0]);
	else
		nbCharDifferent = 0;

	for (int i = 1; i < _hand.size(); i++)
	{
		for (int c = 0; c < characters.size(); c++)
		{
			if (characters[c] == _hand[i] || (isPartTwo && _hand[i] == 'J'))
				isCharExist = true;
		}
		if (!isCharExist)
		{
			characters.push_back(_hand[i]);
			nbCharDifferent += 1;
		}
		else
			isCharExist = false;

		if (nbCharDifferent > 2)
		{
			characters.clear();
			return false;
		}
	}
	characters.clear();
	return true;
}

bool checkThreeOfHands(const std::string& _hand, const std::vector<char>& _cards, const bool& isPartTwo)
{
	int nb = 0;

	for (int x = 0; x < _cards.size(); x++)
	{
		for (int y = 0; y < _hand.size(); y++)
		{
			if (_hand[y] == _cards[x] || (isPartTwo && _hand[y] == 'J'))
				nb += 1;
		}
		if (nb == 3)
			return true;
		else
			nb = 0;
	}
	return false;
}

bool checkTwoPairHands(const std::string& _hand, const std::vector<char>& _cards, const bool& isPartTwo)
{
	std::vector<char>	characters;
	bool				isCharExist = false;

	int nbCharDifferent = 1;

	if (!isPartTwo || (isPartTwo && _hand[0] != 'J'))
		characters.push_back(_hand[0]);

	for (int i = 1; i < _hand.size(); i++)
	{
		for (int c = 0; c < characters.size(); c++)
		{
			if (characters[c] == _hand[i] || (isPartTwo && _hand[i] == 'J'))
				isCharExist = true;
		}
		if (!isCharExist)
		{
			characters.push_back(_hand[i]);
			nbCharDifferent += 1;
		}
		else
			isCharExist = false;

		if (nbCharDifferent > 3)
		{
			characters.clear();
			return false;
		}
	}
	characters.clear();
	return true;
}

bool checkPairHands(const std::string& _hand, const std::vector<char>& _cards, const bool& isPartTwo)
{
	std::vector<char>	characters;
	bool				isCharExist = false;

	int nbCharDifferent = 1;

	if (!isPartTwo || (isPartTwo && _hand[0] != 'J'))
		characters.push_back(_hand[0]);
	else
		nbCharDifferent = 0;

	for (int i = 1; i < _hand.size(); i++)
	{
		for (int c = 0; c < characters.size(); c++)
		{
			if (characters[c] == _hand[i] || (isPartTwo && _hand[i] == 'J'))
				isCharExist = true;
		}
		if (!isCharExist)
		{
			characters.push_back(_hand[i]);
			nbCharDifferent += 1;
		}
		else
			isCharExist = false;

	}
	if (nbCharDifferent != 4)
	{
		characters.clear();
		return false;
	}
	characters.clear();
	return true;
}


void getCardValues(const std::vector<char>& _cards, const char& cardA, const char& cardB, char& a, char& b)
{
	for (int i = 0; i < _cards.size(); i++)
	{
		if (_cards[i] == cardA)
			a = i;
	}
	for (int j = 0; j < _cards.size(); j++)
	{
		if (_cards[j] == cardB)
			b = j;
	}
}

void sortHighCardHands(std::vector<t_PokerHand>& _hands, const std::vector<char>& _cards)
{
	bool isSorted = false;
	t_PokerHand	tmp;

	char a = -1;
	char b = -1;

	while (!isSorted)
	{
		isSorted = true;
		for (int i = 0; i < _hands.size() - 1; i++) // FOR EACH HAND
		{
			for (int j = 0; j < _hands[i].cards.size() && isSorted && a == b; j++) // FOR EACH CARD IN THE HAND
			{
				getCardValues(_cards, _hands[i].cards[j], _hands[i + 1].cards[j], a, b);
				if (a > b)
				{
					tmp = _hands[i];
					_hands[i] = _hands[i + 1];
					_hands[i + 1] = tmp;
					isSorted = false;
				}
			}
			a = -1;
			b = -1;
		}
	}
}

void daySeven(const bool& isPartTwo)
{
	FileParser	_fileParser("2023\\InputFiles\\inputD7.txt");

	std::vector<char>				cards;
	std::string						word;

	std::vector<t_PokerHand>		hands;
	t_PokerHand						tmpHand;

	std::vector<t_PokerHand>		highCardHands;
	std::vector<t_PokerHand>		PairHands;
	std::vector<t_PokerHand>		TwoPairHands;
	std::vector<t_PokerHand>		ThreeOfHands;
	std::vector<t_PokerHand>		FullHands;
	std::vector<t_PokerHand>		FourOfHands;
	std::vector<t_PokerHand>		FiveOfHands;

	t_HandType						hand = FIVEOFAKIND;

	unsigned long long int			finalValue = 0;

	initCardValues(cards, isPartTwo);

	while ((word = _fileParser.readWordToString()) != "")
	{
		tmpHand.cards = word;
		word = _fileParser.readWordToString();
		tmpHand.bid = std::stoi(word);

		hands.push_back(tmpHand);
	}

	for (int x = 0; x < hands.size(); x++)
	{
		if (checkFiveOfHands(hands[x].cards, isPartTwo))
		{
			t_PokerHand tmp = hands[x];
			hands[x] = hands[hands.size() - 1];
			hands[hands.size() - 1] = tmp;

			FiveOfHands.push_back(tmp);
			hands.pop_back();

			x -= 1;
		}
		else if (checkFourOfHands(hands[x].cards, cards, isPartTwo))
		{
			t_PokerHand tmp = hands[x];
			hands[x] = hands[hands.size() - 1];
			hands[hands.size() - 1] = tmp;

			FourOfHands.push_back(tmp);
			hands.pop_back();

			x -= 1;
		}
		else if (checkFullHouseHands(hands[x].cards, cards, isPartTwo))
		{
			t_PokerHand tmp = hands[x];
			hands[x] = hands[hands.size() - 1];
			hands[hands.size() - 1] = tmp;

			FullHands.push_back(tmp);
			hands.pop_back();

			x -= 1;
		}
		else if (checkThreeOfHands(hands[x].cards, cards, isPartTwo))
		{
			t_PokerHand tmp = hands[x];
			hands[x] = hands[hands.size() - 1];
			hands[hands.size() - 1] = tmp;

			ThreeOfHands.push_back(tmp);
			hands.pop_back();

			x -= 1;
		}
		else if (checkTwoPairHands(hands[x].cards, cards, isPartTwo))
		{
			t_PokerHand tmp = hands[x];
			hands[x] = hands[hands.size() - 1];
			hands[hands.size() - 1] = tmp;

			TwoPairHands.push_back(tmp);
			hands.pop_back();

			x -= 1;
		}
		else if (checkPairHands(hands[x].cards, cards, isPartTwo))
		{
			t_PokerHand tmp = hands[x];
			hands[x] = hands[hands.size() - 1];
			hands[hands.size() - 1] = tmp;

			PairHands.push_back(tmp);
			hands.pop_back();

			x -= 1;
		}
		else
		{
			t_PokerHand tmp = hands[x];
			hands[x] = hands[hands.size() - 1];
			hands[hands.size() - 1] = tmp;

			highCardHands.push_back(tmp);
			hands.pop_back();

			x -= 1;
		}
	}

	if (highCardHands.size() > 0)
		sortHighCardHands(highCardHands, cards);
	if (PairHands.size() > 0)
		sortHighCardHands(PairHands, cards);
	if (TwoPairHands.size() > 0)
		sortHighCardHands(TwoPairHands, cards);
	if (ThreeOfHands.size() > 0)
		sortHighCardHands(ThreeOfHands, cards);
	if (FullHands.size() > 0)
		sortHighCardHands(FullHands, cards);
	if (FourOfHands.size() > 0)
		sortHighCardHands(FourOfHands, cards);
	if (FiveOfHands.size() > 0)
		sortHighCardHands(FiveOfHands, cards);

	unsigned int	range = 1;

	for (int i = 0; i < highCardHands.size(); i++)
	{
		finalValue += range * highCardHands[i].bid;
		range += 1;
	}
	for (int i = 0; i < PairHands.size(); i++)
	{
		finalValue += range * PairHands[i].bid;
		range += 1;
	}
	for (int i = 0; i < TwoPairHands.size(); i++)
	{
		finalValue += range * TwoPairHands[i].bid;
		range += 1;
	}
	for (int i = 0; i < ThreeOfHands.size(); i++)
	{
		finalValue += range * ThreeOfHands[i].bid;
		range += 1;
	}
	for (int i = 0; i < FullHands.size(); i++)
	{
		finalValue += range * FullHands[i].bid;
		range += 1;
	}
	for (int i = 0; i < FourOfHands.size(); i++)
	{
		finalValue += range * FourOfHands[i].bid;
		range += 1;
	}
	for (int i = 0; i < FiveOfHands.size(); i++)
	{
		finalValue += range * FiveOfHands[i].bid;
		range += 1;
	}
	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}
