#pragma once

#include "FileParser.h"
#include <vector>
#include <Windows.h>

typedef struct s_Coor
{
	int		x;
	int		y;
} t_Coor;

typedef struct s_Tree
{
	int		height;
	t_Coor	pos;

	int		scenicScore;
} t_Tree;

bool		isVisibleFromLeft(const std::vector<t_Tree>& line, const t_Coor& coor);
bool		isVisibleFromRight(const std::vector<t_Tree>& line, const t_Coor& coor);
bool		isVisibleFromTop(const std::vector<std::vector<t_Tree> >& map, const t_Coor& coor);
bool		isVisibleFromBottom(const std::vector<std::vector<t_Tree> >& map, const t_Coor& coor);

int			calcScenicScoreFromLeft(const std::vector<t_Tree>& line, const t_Coor& coor);
int			calcScenicScoreFromRight(const std::vector<t_Tree>& line, const t_Coor& coor);
int			calcScenicScoreFromTop(const std::vector<std::vector<t_Tree> >& map, const t_Coor& coor);
int			calcScenicScoreFromBottom(const std::vector<std::vector<t_Tree> >& map, const t_Coor& coor);

void		dayEight(bool isPartTwo = false);