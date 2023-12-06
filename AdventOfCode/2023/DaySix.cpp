#include "DaySix.h"

bool isNumberD6(const std::string& _word)
{
	if (_word.size() == 0)
		return false;
	for (int i = 0; i < _word.size(); i++)
	{
		if (_word[i] < '0' || _word[i] > '9')
			return false;
	}
	return true;
}

void	calcValue(std::vector<unsigned int>& _times, std::vector< unsigned int>& _distances, unsigned long long int& _finalValue)
{
	unsigned int	timeLeft;
	unsigned int	speed;
	unsigned int	nbWaysCorrect = 0;

	for (int i = 0; i < _times.size(); i++)
	{
		timeLeft = _times[i];
		speed = 0;
		while (timeLeft * speed <= _distances[i])
		{
			timeLeft -= 1;
			speed += 1;
		}
		nbWaysCorrect = timeLeft - speed + 1;
		_finalValue *= nbWaysCorrect;
	}
}

unsigned long long int calcValuePartTwo(unsigned long long& _time, unsigned long long& _distance)
{
	unsigned long long int	timeLeft;
	unsigned long long int	speed;
	unsigned long long int	nbWaysCorrect = 0;

	timeLeft = _time;
	speed = 0;
	while (timeLeft * speed <= _distance)
	{
		timeLeft -= 1;
		speed += 1;
	}
	nbWaysCorrect = timeLeft - speed + 1;

	return nbWaysCorrect;
}

void daySix(const bool& isPartTwo)
{
	FileParser	_fileParser("2023\\InputFiles\\inputD6.txt");
	std::string	word;

	unsigned long long int		finalValue = 1;

	std::vector<unsigned int>	times;
	std::vector<unsigned int>	distances;

	std::string					time = "";
	std::string					distance = "";

	t_RecordState				state = INIT;

	if (!isPartTwo)
	{
		while (state != FINISHED && (word = _fileParser.readWordToString()) != "")
		{
			if (word == "Time:")
				state = TIME;
			else if (word == "Distance:")
				state = DISTANCE;
			else if (isNumberD6(word))
			{
				if (state == TIME)
					times.push_back(std::stoi(word));
				else
					distances.push_back(std::stoi(word));
			}
			else if (word == "")
				state = FINISHED;
		}
	}
	else
	{
		while (state != FINISHED && (word = _fileParser.readWordToString()) != "")
		{
			if (word == "Time:")
				state = TIME;
			else if (word == "Distance:")
				state = DISTANCE;
			else if (isNumberD6(word))
			{
				if (state == TIME)
					time = time + word;
				else
					distance = distance + word;
			}
			else if (word == "")
				state = FINISHED;
		}
	}

	if (!isPartTwo)
		calcValue(times, distances, finalValue);
	else
	{
		unsigned long long int timeNb = std::stoull(time);
		unsigned long long int distanceNb = std::stoull(distance);

		finalValue = calcValuePartTwo(timeNb, distanceNb);
	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}
