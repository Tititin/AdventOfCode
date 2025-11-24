#pragma once

#include "FileParser.h"

typedef struct		s_Xmas
{
	unsigned int	x = 0;
	unsigned int	m = 0;
	unsigned int	a = 0;
	unsigned int	s = 0;

	unsigned long int	totalValue = 0;
}					t_Xmas;

typedef struct		s_XmasPartTwo
{
	unsigned int	minX = 1;
	unsigned int	maxX = 4000;

	unsigned int	minM = 1;
	unsigned int	maxM = 4000;
	
	unsigned int	minA = 1;
	unsigned int	maxA = 4000;

	unsigned int	minS = 1;
	unsigned int	maxS = 4000;
}					t_XmasPartTwo;

typedef enum		e_ConditionType
{
	NODE = 0,
	CONDITION = 1
}					t_ConditionType;

typedef struct		s_Condition
{
	char			valueToTest = 'x';
	bool			isOperandGreaterThan = false;
	int				thresholdValue = 0;

	t_ConditionType	type;

	std::string		resultIfTrue = "";
}					t_Condition;

typedef struct		s_Node
{
	std::vector<std::string>	conditions;
}					t_Node;

void	resetXmasObject(t_Xmas& _xmas);
void	populateXmasObject(const std::string& _valueLine, t_Xmas& _xmas);

void	runNode(std::map<std::string, t_Node>& const nodes, const std::string& _nodeName, t_XmasPartTwo _xmas);

std::string	verifyCondition(const t_Xmas& _xmas, const std::string& _condition);
t_Condition convertConditionString(const std::string& _condition);

void dayNineteen(const bool& isPartTwo = false);