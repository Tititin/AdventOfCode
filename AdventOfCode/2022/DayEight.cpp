#include "DayEight.h"

bool isVisibleFromLeft(const std::vector<t_Tree>& line, const t_Coor& coor)
{
	bool isVisible = true;

	for (int i = 0; i < coor.x; i++)
		if (line[i].height >= line[coor.x].height)
			isVisible = false;

	return (isVisible);
}

bool isVisibleFromRight(const std::vector<t_Tree>& line, const t_Coor& coor)
{
	bool isVisible = true;

	for (int i = coor.x + 1; i < line.size(); i++)
		if (line[i].height >= line[coor.x].height)
			isVisible = false;

	return (isVisible);
}

bool isVisibleFromTop(const std::vector<std::vector<t_Tree>>& map, const t_Coor& coor)
{
	bool isVisible = true;

	for (int y = 0; y < coor.y; y++)
		if (map[y][coor.x].height >= map[coor.y][coor.x].height)
			isVisible = false;

	return (isVisible);
}

bool isVisibleFromBottom(const std::vector<std::vector<t_Tree>>& map, const t_Coor& coor)
{
	bool isVisible = true;

	for (int y = coor.y + 1; y < map.size(); y++)
		if (map[y][coor.x].height >= map[coor.y][coor.x].height)
			isVisible = false;

	return (isVisible);
}

int calcScenicScoreFromLeft(const std::vector<t_Tree>& line, const t_Coor& coor)
{
	int scenicScore = 0;
	bool stopCheck = false;

	for (int i = coor.x - 1; i >= 0 && !stopCheck; i--)
	{
		if (line[i].height >= line[coor.x].height)
			stopCheck = true;
		scenicScore += 1;
	}

	return (scenicScore);
}

int calcScenicScoreFromRight(const std::vector<t_Tree>& line, const t_Coor& coor)
{
	int scenicScore = 0;
	bool stopCheck = false;

	for (int i = coor.x + 1; i < line.size() && !stopCheck; i++)
	{
		if (line[i].height >= line[coor.x].height)
			stopCheck = true;
		scenicScore += 1;
	}

	return (scenicScore);
}

int calcScenicScoreFromTop(const std::vector<std::vector<t_Tree>>& map, const t_Coor& coor)
{
	int scenicScore = 0;
	bool stopCheck = false;

	for (int y = coor.y - 1; y >= 0 && !stopCheck; y--)
	{
		if (map[y][coor.x].height >= map[coor.y][coor.x].height)
			stopCheck = true;
		scenicScore += 1;
	}

	return (scenicScore);
}

int calcScenicScoreFromBottom(const std::vector<std::vector<t_Tree>>& map, const t_Coor& coor)
{
	int scenicScore = 0;
	bool stopCheck = false;

	for (int y = coor.y + 1; y < map.size() && !stopCheck; y++)
	{
		if (map[y][coor.x].height >= map[coor.y][coor.x].height)
			stopCheck = true;
		scenicScore += 1;
	}

	return (scenicScore);
}

void dayEight(bool isPartTwo)
{
	FileParser							fileParser("2022\\InputFiles\\inputD8.txt");
	std::vector<std::vector<t_Tree> >	map;
	std::vector<t_Tree>					mapLine;
	std::string							line;

	t_Tree								tree;
	int									x = 0;
	int									y = 0;

	int									visibleTreesCount = 0;
	int									scenicScore = 0;
	int									maxScenicScore = 0;

	while ((line = fileParser.readMap()) != "")
	{
		for (int i = 0; i < line.size(); i++)
		{
			tree.height = line[i] - 48;
			tree.pos = t_Coor{x++, y};

			mapLine.push_back(tree);
		}
		map.push_back(mapLine);
		mapLine.clear();
		x = 0;
		y += 1;
	}

	x = 0;
	y = 0;

	while (y < map.size())
	{
		while (x < map[y].size())
		{
			if (isVisibleFromLeft(map[y], map[y][x].pos)
				|| isVisibleFromRight(map[y], map[y][x].pos)
				|| isVisibleFromTop(map, map[y][x].pos)
				|| isVisibleFromBottom(map, map[y][x].pos))
			{
				visibleTreesCount += 1;
			}
			x += 1;
		}
		x = 0;
		y += 1;
	}

	if (!isPartTwo)
		std::cout << visibleTreesCount << std::endl;
	else
	{
		x = 0;
		y = 0;
		
		while (y < map.size())
		{
			while (x < map[y].size())
			{
				t_Coor coor = t_Coor{ x, y };
				scenicScore = calcScenicScoreFromLeft(map[y], coor)
								* calcScenicScoreFromRight(map[y], coor)
								* calcScenicScoreFromTop(map, coor)
								* calcScenicScoreFromBottom(map, coor);

				if (scenicScore > maxScenicScore)
					maxScenicScore = scenicScore;
				x += 1;
			}
			x = 0;
			y += 1;
		}

		std::cout << maxScenicScore << std::endl;
	}
}
