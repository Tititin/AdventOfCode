#pragma once

#ifndef DAYSEVEN_H_
# define DAYSEVEN_H_

#include "FileParser.h"

typedef struct		s_PokerHand
{
	std::string		cards = "";
	unsigned int	bid = -1;
}					t_PokerHand;

typedef enum		e_HandType
{
	HIGHCARD,
	PAIR,
	TWOPAIR,
	THREEOFAKIND,
	FULLHOUSE,
	FOUROFAKIND,
	FIVEOFAKIND,
	ENDING
}					t_HandType;

void	initCardValues(std::vector<char>& _cards, const bool& isPartTwo = false);

bool	checkFiveOfHands(const std::string& _hand, const bool& isPartTwo = false);
bool	checkFourOfHands(const std::string& _hand, const std::vector<char>& _cards, const bool& isPartTwo = false);
bool	checkFullHouseHands(const std::string& _hand, const std::vector<char>& _cards, const bool& isPartTwo = false);
bool	checkThreeOfHands(const std::string& _hand, const std::vector<char>& _cards, const bool& isPartTwo = false);
bool	checkTwoPairHands(const std::string& _hand, const std::vector<char>& _cards, const bool& isPartTwo = false);
bool	checkPairHands(const std::string& _hand, const std::vector<char>& _cards, const bool& isPartTwo = false);

void	sortHighCardHands(std::vector<t_PokerHand>& _hands, const std::vector<char>& _cards);

void	daySeven(const bool& isPartTwo = false);

#endif // !DAYSEVEN_H_
