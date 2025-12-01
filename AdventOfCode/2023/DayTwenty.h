#pragma once

#include "FileParser.h"
#include <queue>

//typedef enum		e_Pulse
//{
//	LOW = 0,
//	HIGH = 1
//}					t_Pulse;

enum class Pulse : uint8_t { LOW = 0, HIGH = 1 };

inline Pulse		operator!(Pulse p);

typedef enum		e_ModuleStatus
{
	OFF = 0,
	ON = 1
}					t_ModuleStatus;

typedef enum		e_ModuleType
{
	COMMON = 0,
	FLIPFLOP = 1,
	CONJUNCTION = 2
}					t_ModuleType;

typedef struct		s_Signal
{
	std::string		destModule;
	std::string		srcModule;
	Pulse			pulse;
}					t_Signal;

typedef struct		s_Module
{
	t_ModuleStatus	status = OFF;
	t_ModuleType	type = COMMON;
	std::vector<std::string>	destModules;

	void			receiveSignal(const t_Signal& _signal);
	void			sendSignal(const t_Signal& _signal);
}					t_Module;

void	dayTwenty(const bool& isPartTwo = false);
