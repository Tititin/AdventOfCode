#include "DayNineteen.h"

unsigned long long int finalValue = 0;

void resetXmasObject(t_Xmas& _xmas)
{
	_xmas.x = 0;
	_xmas.m = 0;
	_xmas.a = 0;
	_xmas.s = 0;

	_xmas.totalValue = 0;
}

void populateXmasObject(const std::string& _valueLine, t_Xmas& _xmas)
{
	size_t	pos = _valueLine.find('=');
	unsigned int nb = std::stoi(_valueLine.substr(pos + 1));

	if (_valueLine[0] == 'x')
		_xmas.x = nb;
	else if (_valueLine[0] == 'm')
		_xmas.m = nb;
	else if (_valueLine[0] == 'a')
		_xmas.a = nb;
	else
		_xmas.s = nb;

	_xmas.totalValue += nb;
}

void runNode(std::map<std::string, t_Node>& const nodes, const std::string& _nodeName, t_XmasPartTwo _xmas)
{
	t_Condition	condition;

	t_XmasPartTwo	copyA = _xmas;
	t_XmasPartTwo	copyB;

	for (int i = 0; i < nodes[_nodeName].conditions.size(); i++)
	{
		if (i % 2 == 0)
			copyB = copyA;
		else
			copyA = copyB;

		condition = convertConditionString(nodes[_nodeName].conditions[i]);
		if (condition.type == NODE)
		{
			if (condition.resultIfTrue == "A")
			{
				unsigned long long int x;
				unsigned long long int m;
				unsigned long long int a;
				unsigned long long int s;

				if (i % 2 == 0)
				{
					x = copyA.maxX - copyA.minX + 1;
					m = copyA.maxM - copyA.minM + 1;
					a = copyA.maxA - copyA.minA + 1;
					s = copyA.maxS - copyA.minS + 1;
				}
				else
				{
					x = copyB.maxX - copyB.minX + 1;
					m = copyB.maxM - copyB.minM + 1;
					a = copyB.maxA - copyB.minA + 1;
					s = copyB.maxS - copyB.minS + 1;
				}

				finalValue += (x * m * a * s);
			}
			else if (condition.resultIfTrue != "R")
			{
				if (i % 2 == 0)
					runNode(nodes, condition.resultIfTrue, copyA);
				else
					runNode(nodes, condition.resultIfTrue, copyB);
			}
		}
		else
		{
			switch (condition.valueToTest)
			{
			case 'x':
				if (i % 2 == 0)
				{
					if (condition.isOperandGreaterThan && condition.thresholdValue + 1 > copyA.minX)
					{
						copyA.minX = condition.thresholdValue + 1;
						copyB.maxX = condition.thresholdValue;
					}
					else if (condition.thresholdValue - 1 < copyA.maxX)
					{
						copyA.maxX = condition.thresholdValue - 1;
						copyB.minX = condition.thresholdValue;
					}
				}
				else
				{
					if (condition.isOperandGreaterThan && condition.thresholdValue + 1 > copyB.minX)
					{
						copyB.minX = condition.thresholdValue + 1;
						copyA.maxX = condition.thresholdValue;
					}
					else if (condition.thresholdValue - 1 < copyB.maxX)
					{
						copyB.maxX = condition.thresholdValue - 1;
						copyA.minX = condition.thresholdValue;
					}
				}
				break;
			case 'm':
				if (i % 2 == 0)
				{
					if (condition.isOperandGreaterThan && condition.thresholdValue + 1 > copyA.minM)
					{
						copyA.minM = condition.thresholdValue + 1;
						copyB.maxM = condition.thresholdValue;
					}
					else if (condition.thresholdValue - 1 < copyA.maxM)
					{
						copyA.maxM = condition.thresholdValue - 1;
						copyB.minM = condition.thresholdValue;
					}
				}
				else
				{
					if (condition.isOperandGreaterThan && condition.thresholdValue + 1 > copyB.minM)
					{
						copyB.minM = condition.thresholdValue + 1;
						copyA.maxM = condition.thresholdValue;
					}
					else if (condition.thresholdValue - 1 < copyB.maxM)
					{
						copyB.maxM = condition.thresholdValue - 1;
						copyA.minM = condition.thresholdValue;
					}
				}
				break;
			case 'a':
				if (i % 2 == 0)
				{
					if (condition.isOperandGreaterThan && condition.thresholdValue + 1 > copyA.minA)
					{
						copyA.minA = condition.thresholdValue + 1;
						copyB.maxA = condition.thresholdValue;
					}
					else if (condition.thresholdValue - 1 < copyA.maxA)
					{
						copyA.maxA = condition.thresholdValue - 1;
						copyB.minA = condition.thresholdValue;
					}
				}
				else
				{
					if (condition.isOperandGreaterThan && condition.thresholdValue + 1 > copyB.minA)
					{
						copyB.minA = condition.thresholdValue + 1;
						copyA.maxA = condition.thresholdValue;
					}
					else if (condition.thresholdValue - 1 < copyB.maxA)
					{
						copyB.maxA = condition.thresholdValue - 1;
						copyA.minA = condition.thresholdValue;
					}
				}
				break;
			case 's':
				if (i % 2 == 0)
				{
					if (condition.isOperandGreaterThan && condition.thresholdValue + 1 > copyA.minS)
					{
						copyA.minS = condition.thresholdValue + 1;
						copyB.maxS = condition.thresholdValue;
					}
					else if (condition.thresholdValue - 1 < copyA.maxS)
					{
						copyA.maxS = condition.thresholdValue - 1;
						copyB.minS = condition.thresholdValue;
					}
				}
				else
				{
					if (condition.isOperandGreaterThan && condition.thresholdValue + 1 > copyB.minS)
					{
						copyB.minS = condition.thresholdValue + 1;
						copyA.maxS = condition.thresholdValue;
					}
					else if (condition.thresholdValue - 1 < copyB.maxS)
					{
						copyB.maxS = condition.thresholdValue - 1;
						copyA.minS = condition.thresholdValue;
					}
				}
				break;
			}
			if (condition.resultIfTrue != "A" && condition.resultIfTrue != "R")
			{
				if (i % 2 == 0)
					runNode(nodes, condition.resultIfTrue, copyA);
				else
					runNode(nodes, condition.resultIfTrue, copyB);
			}
			else if (condition.resultIfTrue == "A")
			{
				unsigned long long int x;
				unsigned long long int m;
				unsigned long long int a;
				unsigned long long int s;

				if (i % 2 == 0)
				{
					x = copyA.maxX - copyA.minX + 1;
					m = copyA.maxM - copyA.minM + 1;
					a = copyA.maxA - copyA.minA + 1;
					s = copyA.maxS - copyA.minS + 1;
				}
				else
				{
					x = copyB.maxX - copyB.minX + 1;
					m = copyB.maxM - copyB.minM + 1;
					a = copyB.maxA - copyB.minA + 1;
					s = copyB.maxS - copyB.minS + 1;
				}

				finalValue += (x * m * a * s);
			}
		}
	}
}

std::string verifyCondition(const t_Xmas& _xmas, const std::string& _condition)
{
	unsigned int	nb = 0;
	size_t			pos = _condition.find(':');
	std::string		nextMove = "";

	if (pos == std::string::npos)
		return _condition;
	else
	{
		nb = std::stoi(_condition.substr(2));
		nextMove = _condition.substr(pos + 1);
	}

	//std::cout << "== CONDITION ANALYSIS ==" << std::endl;
	//std::cout << "VALUE TO TEST : " << _condition[0] << std::endl;
	//std::cout << "OPERATOR : " << _condition[1] << std::endl;
	//std::cout << "THRESHOLD VALUE : " << nb << std::endl;
	//std::cout << "NEXT MOVE IF VERIFIED : " << nextMove << std::endl;

	//std::cout << std::endl;

	switch (_condition[0])
	{
	case 'x':
		if (_condition[1] == '<' && _xmas.x < nb)
			return nextMove;
		else if (_condition[1] == '>' && _xmas.x > nb)
			return nextMove;
		break;
	case 'm':
		if (_condition[1] == '<' && _xmas.m < nb)
			return nextMove;
		else if (_condition[1] == '>' && _xmas.m > nb)
			return nextMove;
		break;
	case 'a':
		if (_condition[1] == '<' && _xmas.a < nb)
			return nextMove;
		else if (_condition[1] == '>' && _xmas.a > nb)
			return nextMove;
		break;
	case 's':
		if (_condition[1] == '<' && _xmas.s < nb)
			return nextMove;
		else if (_condition[1] == '>' && _xmas.s > nb)
			return nextMove;
		break;
	}
	return "";
}

t_Condition convertConditionString(const std::string& _condition)
{
	size_t			pos = _condition.find(':');
	t_Condition		result;

	if (pos == std::string::npos)
	{
		result.resultIfTrue = _condition;
		result.type = NODE;
	}
	else
	{
		result.valueToTest = _condition[0];
		if (_condition[1] == '>')
			result.isOperandGreaterThan = true;
		result.thresholdValue = std::stoi(_condition.substr(2));
		result.resultIfTrue = _condition.substr(pos + 1);
		result.type = CONDITION;
	}

	return result;
}

void dayNineteen(const bool& isPartTwo)
{
	FileParser	_fileParser("2023\\InputFiles\\inputD19.txt");
	std::string	line;

	t_Xmas							currentXmas;
	std::vector<t_Xmas>				xmasArray;

	std::string						nodeName;
	t_Node							currentNode;
	std::map<std::string, t_Node>	nodes;

	t_XmasPartTwo					xmasPartTwo;

	// BUILDING NODES
	while ((line = _fileParser.readLineToString()) != "")
	{
		size_t	pos = line.find('{');
		size_t	tmpPos = pos + 1;
		size_t	endPos = line.find('}');

		nodeName = line.substr(0, pos);
		nodes.insert(std::pair<std::string, t_Node>(nodeName, currentNode));

		while (line.find(',', pos + 1) != std::string::npos)
		{
			tmpPos = line.find(',', pos + 1);
			nodes[nodeName].conditions.push_back(line.substr(pos + 1, tmpPos - pos - 1));
			pos = tmpPos;
		}
		nodes[nodeName].conditions.push_back(line.substr(pos + 1, endPos - pos - 1));
	}

	// BUILDING XMAS ARRAY
	if (!isPartTwo)
	{
		while ((line = _fileParser.readLineToString()) != "")
		{
			size_t	pos = line.find('{');
			size_t	tmpPos;
			size_t	endPos = line.find('}');

			resetXmasObject(currentXmas);
			while (line.find(',', pos + 1) != std::string::npos)
			{
				tmpPos = line.find(',', pos + 1);
				populateXmasObject(line.substr(pos + 1, tmpPos - pos - 1), currentXmas);
				pos = tmpPos;
			}
			populateXmasObject(line.substr(pos + 1, endPos - pos - 1), currentXmas);
			xmasArray.push_back(currentXmas);
		}
	}

	currentNode = nodes["in"];

	if (!isPartTwo)
	{
		for (int i = 0; i < xmasArray.size(); i++)
		{
			std::string	nextMove = "";
			bool		isRunning = true;

			while (isRunning)
			{
				for (int j = 0; j < currentNode.conditions.size() && nextMove == ""; j++)
					nextMove = verifyCondition(xmasArray[i], currentNode.conditions[j]);

				if (nextMove == "A" || nextMove == "R")
				{
					isRunning = false;
					if (nextMove == "A")
						finalValue += xmasArray[i].totalValue;
					currentNode = nodes["in"];
				}
				else
					currentNode = nodes[nextMove];
				nextMove = "";
			}
		}
	}
	else
	{
		runNode(nodes, "in", xmasPartTwo);
	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}
