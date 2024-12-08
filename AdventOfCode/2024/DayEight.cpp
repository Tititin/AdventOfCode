#include "DayEight.h"

t_Pos& operator-(const t_Pos& left, const t_Pos& right)
{
	t_Pos	result;

	result.x = left.x - right.x;
	result.y = left.y - right.y;

	return (result);
}

t_Pos& operator+(const t_Pos& left, const t_Pos& right)
{
	t_Pos	result;

	result.x = left.x + right.x;
	result.y = left.y + right.y;

	return (result);
}

bool isAntinodeUnique(const t_Pos& _pos, const std::vector<t_Pos>& _antinodes)
{
	bool	isUnique = true;

	for (int i = 0; i < _antinodes.size() && isUnique; i++)
	{
		if (_antinodes[i].x == _pos.x && _antinodes[i].y == _pos.y)
			isUnique = false;
	}

	return isUnique;
}

void dayEight(const bool& isPartTwo)
{
	FileParser	_file("2024\\InputFiles\\inputD8.txt");
	std::string	line;
	unsigned long long int	finalValue = 0;

	std::vector<std::string>	antennaMap;
	t_Pos						currentPos = t_Pos{ 0, 0 };
	std::vector<std::string>	antinodesMap;
	std::vector<t_Pos>			antinodesPositionsVector;

	std::map<char, std::vector<t_Pos>>	antennaPos;
	std::vector<t_Pos>	tmp;

	while ((line = _file.readLineToString()) != "")
	{
		antennaMap.push_back(line);
		antinodesMap.push_back(std::string(line.size(), '.'));

		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] != '.')
			{
				if (antennaPos.find(line[i]) != antennaPos.end())
					antennaPos[line[i]].push_back(t_Pos{ i, currentPos.y });
				else
				{
					tmp.push_back(t_Pos{ i, currentPos.y });
					antennaPos.insert(std::pair<char, std::vector<t_Pos>>(line[i], tmp));
					tmp.clear();
				}
				if (isPartTwo)
					antinodesPositionsVector.push_back(t_Pos{ i, currentPos.y });
			}
		}
		currentPos.y += 1;
	}

	for (auto frequency : antennaPos)
	{
		t_Pos	antinodePos;

		tmp = frequency.second;

		for (int i = 0; i < tmp.size() - 1; i++)
		{
			for (int j = i + 1; j < tmp.size(); j++)
			{
				antinodePos.x = tmp[j].x - tmp[i].x;
				antinodePos.y = tmp[j].y - tmp[i].y;

				if (!isPartTwo)
				{

					t_Pos	antinodeTwo = tmp[i] - antinodePos;
					t_Pos	antinodeThree = tmp[j] + antinodePos;

					if (antinodeTwo.x >= 0 && antinodeTwo.x < antennaMap[0].size()
						&& antinodeTwo.y >= 0 && antinodeTwo.y < antennaMap.size())
					{
						if (isAntinodeUnique(antinodeTwo, antinodesPositionsVector))
						{
							antinodesPositionsVector.push_back(antinodeTwo);
							antinodesMap[antinodeTwo.y][antinodeTwo.x] = '#';
						}
					}
					if (antinodeThree.x >= 0 && antinodeThree.x < antennaMap[0].size()
						&& antinodeThree.y >= 0 && antinodeThree.y < antennaMap.size())
					{
						if (isAntinodeUnique(antinodeThree, antinodesPositionsVector))
						{
							antinodesPositionsVector.push_back(antinodeThree);
							antinodesMap[antinodeThree.y][antinodeThree.x] = '#';
						}
					}
				}
				else
				{
					t_Pos	antinodeOne = tmp[i] - antinodePos;
					t_Pos	antinodeTwo = tmp[j] + antinodePos;

					while (antinodeOne.x >= 0 && antinodeOne.x < antennaMap[0].size()
						&& antinodeOne.y >= 0 && antinodeOne.y < antennaMap.size())
					{
						if (isAntinodeUnique(antinodeOne, antinodesPositionsVector))
						{
							antinodesPositionsVector.push_back(antinodeOne);
							antinodesMap[antinodeOne.y][antinodeOne.x] = '#';
						}
						antinodeOne = antinodeOne - antinodePos;
					}
					while (antinodeTwo.x >= 0 && antinodeTwo.x < antennaMap[0].size()
						&& antinodeTwo.y >= 0 && antinodeTwo.y < antennaMap.size())
					{
						if (isAntinodeUnique(antinodeTwo, antinodesPositionsVector))
						{
							antinodesPositionsVector.push_back(antinodeTwo);
							antinodesMap[antinodeTwo.y][antinodeTwo.x] = '#';
						}
						antinodeTwo = antinodeTwo + antinodePos;
					}
				}
			}
		}
	}

	currentPos.y = 0;
	finalValue = antinodesPositionsVector.size();

	//// DEBUG LINES - DISPLAYING THE ANTINODES
	//for (int i = 0; i < antinodesMap.size(); i++)
	//	std::cout << antinodesMap[i] << std::endl;

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}