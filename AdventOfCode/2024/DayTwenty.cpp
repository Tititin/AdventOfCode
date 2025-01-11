#include "DayTwenty.h"

void dayTwenty(const bool& isPartTwo)
{
	FileParser	_file("2024\\InputFiles\\inputD20bis.txt");
	std::string	line;
	unsigned long long int	finalValue = 0;

	std::vector<std::string>	raceTrack;
	std::vector<std::vector<long long int>>	raceDistances;
	std::vector<t_Pos>			raceTrackPositions;

	t_Pos						startPos;
	t_Pos						currentPos;
	t_Pos						endPos;

	while ((line = _file.readLineToString()) != "")
	{
		raceTrack.push_back(line);
		raceDistances.push_back(std::vector<long long int>(line.size(), -2));
	}

	for (int y = 0; y < raceTrack.size(); y++)
	{
		for (int x = 0; x < raceTrack[y].size(); x++)
		{
			if (raceTrack[y][x] != '#')
			{
				raceDistances[y][x] = -1;

				if (raceTrack[y][x] == 'S')
				{
					startPos = t_Pos{ x, y };
					currentPos = startPos;
					raceDistances[y][x] = 0;
					//raceTrackPositions.push_back(startPos);
				}
				else if (raceTrack[y][x] == 'E')
					endPos = t_Pos{ x, y };
			}
		}
	}

	while (raceDistances[endPos.y][endPos.x] == -1)
	{
		long long int	currentDistance = raceDistances[currentPos.y][currentPos.x];

		raceTrackPositions.push_back(currentPos);

		if (currentPos.y - 1 > 0 && raceTrack[currentPos.y - 1][currentPos.x] != '#' && raceDistances[currentPos.y - 1][currentPos.x] == -1)
		{
			raceDistances[currentPos.y - 1][currentPos.x] = currentDistance += 1;
			currentPos.y -= 1;
		}
		else if (currentPos.y + 1 < raceTrack.size() - 1 && raceTrack[currentPos.y + 1][currentPos.x] != '#' && raceDistances[currentPos.y + 1][currentPos.x] == -1)
		{
			raceDistances[currentPos.y + 1][currentPos.x] = currentDistance += 1;
			currentPos.y += 1;
		}
		else if (currentPos.x - 1 > 0 && raceTrack[currentPos.y][currentPos.x - 1] != '#' && raceDistances[currentPos.y][currentPos.x - 1] == -1)
		{
			raceDistances[currentPos.y][currentPos.x - 1] = currentDistance += 1;
			currentPos.x -= 1;
		}
		else if (currentPos.x + 1 < raceTrack[currentPos.y].size() - 1 && raceTrack[currentPos.y][currentPos.x + 1] != '#' && raceDistances[currentPos.y][currentPos.x + 1] == -1)
		{
			raceDistances[currentPos.y][currentPos.x + 1] = currentDistance += 1;
			currentPos.x += 1;
		}
	}

	raceTrackPositions.push_back(endPos);

	if (!isPartTwo)
	{
		for (int i = 0; i < raceTrackPositions.size() - 1; i++)
		{
			t_Pos	currentPos = raceTrackPositions[i];

			if (currentPos.y - 2 > 0 && raceTrack[currentPos.y - 2][currentPos.x] != '#' && raceDistances[currentPos.y - 2][currentPos.x] - raceDistances[currentPos.y][currentPos.x] >= 102)
				finalValue += 1;
			if (currentPos.y + 2 < raceTrack.size() - 1 && raceTrack[currentPos.y + 2][currentPos.x] != '#' && raceDistances[currentPos.y + 2][currentPos.x] - raceDistances[currentPos.y][currentPos.x] >= 102)
				finalValue += 1;
			if (currentPos.x - 2 > 0 && raceTrack[currentPos.y][currentPos.x - 2] != '#' && raceDistances[currentPos.y][currentPos.x - 2] - raceDistances[currentPos.y][currentPos.x] >= 102)
				finalValue += 1;
			if (currentPos.x + 2 < raceTrack[currentPos.y].size() - 1 && raceTrack[currentPos.y][currentPos.x + 2] != '#' && raceDistances[currentPos.y][currentPos.x + 2] - raceDistances[currentPos.y][currentPos.x] >= 102)
				finalValue += 1;
		}
	}
	else
	{
		for (int i = 0; i < raceTrackPositions.size() - 1; i++)
		{
			for (int j = i + 1; j < raceTrackPositions.size(); j++)
			{
				t_Pos	p1 = raceTrackPositions[i];
				t_Pos	p2 = raceTrackPositions[j];

				unsigned long int	distance = abs(p2.x - p1.x + p2.y - p1.y);

				if (distance <= 20)
				{
					if (raceDistances[p2.y][p2.x] - raceDistances[p1.y][p1.x] - distance == 70)
					{
						std::cout << "CHEAT FROM " << p1.x << ";" << p1.y << " TO " << p2.x << ";" << p2.y << " WITH DISTANCE OF " << distance << std::endl;
						finalValue += 1;
					}
				}
			}
		}
	}
	//finalValue = raceDistances[endPos.y][endPos.x];

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}