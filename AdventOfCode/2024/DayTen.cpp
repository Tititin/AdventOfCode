#include "DayTen.h"

unsigned int finalScore = 0;
std::vector<t_Pos>	ninePosGlobal;

void runTrail(t_TrailHead _trail, const std::vector<std::string>& _topoMap)
{
	if (_trail.level == 9)
	{
		finalScore += 1;
		ninePosGlobal.push_back(_trail.currentPos);
	}
	else
	{
		if (_trail.currentPos.y - 1 >= 0 && _topoMap[_trail.currentPos.y - 1][_trail.currentPos.x] - '0' == _trail.level + 1)
			runTrail(t_TrailHead{ _trail.startPos, t_Pos{_trail.currentPos.x, _trail.currentPos.y - 1}, _trail.nineFound, _trail.level + 1, _trail.score }, _topoMap);
		if (_trail.currentPos.x + 1 < _topoMap[0].size() && _topoMap[_trail.currentPos.y][_trail.currentPos.x + 1] - '0' == _trail.level + 1)
			runTrail(t_TrailHead{ _trail.startPos, t_Pos{_trail.currentPos.x + 1, _trail.currentPos.y}, _trail.nineFound, _trail.level + 1, _trail.score }, _topoMap);
		if (_trail.currentPos.y + 1 < _topoMap.size() && _topoMap[_trail.currentPos.y + 1][_trail.currentPos.x] - '0' == _trail.level + 1)
			runTrail(t_TrailHead{ _trail.startPos, t_Pos{_trail.currentPos.x, _trail.currentPos.y + 1}, _trail.nineFound, _trail.level + 1, _trail.score }, _topoMap);
		if (_trail.currentPos.x - 1 >= 0 && _topoMap[_trail.currentPos.y][_trail.currentPos.x - 1] - '0' == _trail.level + 1)
			runTrail(t_TrailHead{ _trail.startPos, t_Pos{_trail.currentPos.x - 1, _trail.currentPos.y}, _trail.nineFound, _trail.level + 1, _trail.score }, _topoMap);
	}
}

void dayTen(const bool& isPartTwo)
{
	FileParser	_file("2024\\InputFiles\\inputD10.txt");
	std::string	line;
	unsigned long long int	finalValue = 0;

	std::vector<std::string>	topographicMap;

	std::vector<t_TrailHead>	starts;
	std::vector<unsigned int>	scores;

	while ((line = _file.readLineToString()) != "")
		topographicMap.push_back(line);

	for (int y = 0; y < topographicMap.size(); y++)
	{
		for (int x = 0; x < topographicMap[y].size(); x++)
		{
			if (topographicMap[y][x] == '0')
			{
				t_Pos	trailStart = t_Pos{ x, y };
				t_TrailHead	trail;

				trail.startPos = trailStart;
				trail.currentPos = trailStart;
				trail.level = 0;
				trail.score = 0;

				starts.push_back(trail);
			}
		}
	}

	for (int i = 0; i < starts.size(); i++)
	{
		runTrail(starts[i], topographicMap);

		if (!isPartTwo)
		{
			bool isFullyUnique = false;

			while (!isFullyUnique)
			{
				isFullyUnique = true;

				for (int x = 0; x < ninePosGlobal.size() - 1; x++)
				{
					for (int y = x + 1; y < ninePosGlobal.size(); y++)
					{
						if (ninePosGlobal[x] == ninePosGlobal[y])
						{
							ninePosGlobal.erase(ninePosGlobal.begin() + y);
							isFullyUnique = false;
							y -= 1;
							finalScore -= 1;
						}
					}
				}
			}
			scores.push_back(finalScore);
			finalScore = 0;
		}
		else
			scores.push_back(ninePosGlobal.size());
		ninePosGlobal.clear();
	}

	for (int i = 0; i < starts.size(); i++)
		finalValue += scores[i];

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}