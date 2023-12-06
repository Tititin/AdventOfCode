#pragma once

#ifndef DAYSIX_H_
# define DAYSIX_H_

#include "FileParser.h"

typedef enum	e_RecordState
{
	INIT,
	TIME,
	DISTANCE,
	FINISHED
}				t_RecordState;

bool			isNumberD6(const std::string& _word);

void			calcValue(std::vector<unsigned int>& _times, std::vector<unsigned int>& _distances, unsigned long long int& _finalValue);
unsigned long long int				calcValuePartTwo(unsigned long long int& _time, unsigned long long int& _distance);

void			daySix(const bool& isPartTwo = false);

#endif // !DAYSIX_H_
