#include "DayTwenty.h"

std::queue<t_Signal>	signals;
unsigned long long int	lowPulses = 0;
unsigned long long int	highPulses = 0;

inline Pulse operator!(Pulse p)
{
	return (p == Pulse::LOW) ? Pulse::HIGH : Pulse::LOW;
}

void dayTwenty(const bool& isPartTwo)
{
	FileParser	_fileParser("2023\\InputFiles\\inputD20bis.txt");
	std::string	line;


}

void s_Module::receiveSignal(const t_Signal& _signal)
{
	switch (type)
	{
	case FLIPFLOP:
		if (_signal.pulse == Pulse::LOW)
			(status == OFF) ? (status = ON) : (status = OFF);
		break;
	case CONJUNCTION:
		break;
	}
}

void s_Module::sendSignal(const t_Signal& _signal)
{
	if (_signal.pulse == LOW)
		lowPulses += 1;
	else
		highPulses += 1;
	signals.push(_signal);
}
