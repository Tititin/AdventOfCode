#pragma once

#include "FileParser.h"
#include "utils.h"

typedef enum	e_ButtonState
{
	STAY = 0,
	INCREASE,
	DECREASE
}				t_ButtonState;

typedef struct	s_ButtonParam
{
	unsigned int	moveX = 0;
	unsigned int	moveY = 0;

	t_ButtonState	state = STAY;
}				t_ButtonParam;

typedef struct	s_ButtonPress
{
	unsigned int	pressA = 0;
	unsigned int	pressB = 0;
}				t_ButtonPress;

typedef struct	s_GameParam
{
	unsigned long long int	goalPosX = 0;
	unsigned long long int	goalPosY = 0;

	t_ButtonParam	buttonA;
	t_ButtonParam	buttonB;

	t_ButtonPress	buttonPress;
}				t_GameParam;

bool	checkEndGame(const t_GameParam& _params);

bool	playGame(t_GameParam& params);
bool	playGamePartTwo(t_GameParam& params);

void dayThirteen(const bool& isPartTwo = false);
