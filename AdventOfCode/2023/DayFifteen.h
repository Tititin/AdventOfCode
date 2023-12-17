#pragma once

#include "FileParser.h"

typedef struct	s_Lens
{
	std::string	label;
	int			focalLength = 0;
}				t_Lens;

unsigned int	calcBoxNumber(const std::string& _label);

void			addOrUpdateBoxes(std::map<int, std::vector<t_Lens >> &_boxes, t_Lens& _lens, const int& boxNb);
void			addOrUpdateBoxes(std::vector<std::vector<t_Lens>>& _boxes, t_Lens& _lens, const int& boxNb);

void			removeLens(std::map<int, std::vector<t_Lens>>& _boxes, t_Lens& _lens);
void			removeLens(std::vector<std::vector<t_Lens>>& _boxes, t_Lens& _lens);

void dayFifteen(const bool& isPartTwo = false);