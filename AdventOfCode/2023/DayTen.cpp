#include "DayTen.h"

bool checkIfPipeline(const std::vector<t_Pos>& _pipePos, const t_Pos& _pos)
{
	for (int i = 0; i < _pipePos.size(); i++)
	{
		if (_pipePos[i].x == _pos.x && _pipePos[i].y == _pos.y)
			return true;
	}

	return false;
}

bool checkOutsideV2(const std::vector<std::string> _pipelineMap, const std::vector<t_Pos>& _pipePos, const t_Pos& _pos)
{
	int nbPipesAbove = 0;
	int nbPipesBelow = 0;
	int nbPipesLeft = 0;
	int nbPipesRight = 0;

	int pipeCorners = 0;
	int pipeDuo = 0;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int y = _pos.y - 1; y >= 0; y--)
	{
		if (checkIfPipeline(_pipePos, t_Pos{ _pos.x, y }))
		{
			if (_pipelineMap[y][_pos.x] == 'F'
				|| _pipelineMap[y][_pos.x] == '7'
				|| _pipelineMap[y][_pos.x] == 'J'
				|| _pipelineMap[y][_pos.x] == 'L')
				pipeDuo += 1;
			if (_pipelineMap[y][_pos.x] == 'F')
				pipeCorners += (1 << 3);
			if (_pipelineMap[y][_pos.x] == '7')
				pipeCorners += (1 << 2);
			if (_pipelineMap[y][_pos.x] == 'J')
				pipeCorners += (1 << 1);
			if (_pipelineMap[y][_pos.x] == 'L')
				pipeCorners += 1;
			if (_pipelineMap[y][_pos.x] == '-')
				nbPipesAbove += 1;
		}
		if (pipeDuo % 2 == 0)
		{
			if (pipeCorners == 10 || pipeCorners == 5)
				nbPipesAbove += 1;
			pipeCorners = 0;
		}
	}
	pipeCorners = 0;

	for (int y = _pos.y + 1; y < _pipelineMap.size(); y++)
	{
		if (checkIfPipeline(_pipePos, t_Pos{ _pos.x, y }))
		{
			if (_pipelineMap[y][_pos.x] == 'F'
				|| _pipelineMap[y][_pos.x] == '7'
				|| _pipelineMap[y][_pos.x] == 'J'
				|| _pipelineMap[y][_pos.x] == 'L')
				pipeDuo += 1;
			if (_pipelineMap[y][_pos.x] == 'F')
				pipeCorners += (1 << 3);
			if (_pipelineMap[y][_pos.x] == '7')
				pipeCorners += (1 << 2);
			if (_pipelineMap[y][_pos.x] == 'J')
				pipeCorners += (1 << 1);
			if (_pipelineMap[y][_pos.x] == 'L')
				pipeCorners += 1;
			if (_pipelineMap[y][_pos.x] == '-')
				nbPipesBelow += 1;
		}
		if (pipeDuo % 2 == 0)
		{
			if (pipeCorners == 10 || pipeCorners == 5)
				nbPipesBelow += 1;
			pipeCorners = 0;
		}
	}
	pipeCorners = 0;

	for (int x = _pos.x + 1; x < _pipelineMap[_pos.y].size(); x++)
	{
		if (checkIfPipeline(_pipePos, t_Pos{ x, _pos.y }))
		{
			if (_pipelineMap[_pos.y][x] == 'F'
				|| _pipelineMap[_pos.y][x] == '7'
				|| _pipelineMap[_pos.y][x] == 'J'
				|| _pipelineMap[_pos.y][x] == 'L')
				pipeDuo += 1;
			if (_pipelineMap[_pos.y][x] == 'F')
				pipeCorners += (1 << 3);
			if (_pipelineMap[_pos.y][x] == '7')
				pipeCorners += (1 << 2);
			if (_pipelineMap[_pos.y][x] == 'J')
				pipeCorners += (1 << 1);
			if (_pipelineMap[_pos.y][x] == 'L')
				pipeCorners += 1;
			if (_pipelineMap[_pos.y][x] == '|')
				nbPipesRight += 1;
		}

		if (pipeDuo % 2 == 0)
		{
			if (pipeCorners == 10 || pipeCorners == 5)
				nbPipesRight += 1;
			pipeCorners = 0;
		}

	}
	pipeCorners = 0;

	for (int x = _pos.x - 1; x >= 0; x--)
	{
		if (checkIfPipeline(_pipePos, t_Pos{ x, _pos.y }))
		{
			if (_pipelineMap[_pos.y][x] == 'F'
				|| _pipelineMap[_pos.y][x] == '7'
				|| _pipelineMap[_pos.y][x] == 'J'
				|| _pipelineMap[_pos.y][x] == 'L')
				pipeDuo += 1;
			if (_pipelineMap[_pos.y][x] == 'F')
				pipeCorners += (1 << 3);
			if (_pipelineMap[_pos.y][x] == '7')
				pipeCorners += (1 << 2);
			if (_pipelineMap[_pos.y][x] == 'J')
				pipeCorners += (1 << 1);
			if (_pipelineMap[_pos.y][x] == 'L')
				pipeCorners += 1;
			if (_pipelineMap[_pos.y][x] == '|')
				nbPipesLeft += 1;
		}
		if (pipeDuo % 2 == 0)
		{
			if (pipeCorners == 10 || pipeCorners == 5)
				nbPipesLeft += 1;
			pipeCorners = 0;
		}
	}

	if ((nbPipesAbove % 2 == 0 || nbPipesBelow % 2 == 0 || nbPipesLeft % 2 == 0 || nbPipesRight % 2 == 0) && !checkIfPipeline(_pipePos, _pos))
		return true;
	return false;
}

void updateDirection(const char& _pipe, t_Direction& direction)
{
	if (_pipe == 'F')
		direction == UP ? direction = RIGHT : direction = DOWN;
	else if (_pipe == '7')
		direction == RIGHT ? direction = DOWN : direction = LEFT;
	else if (_pipe == 'J')
		direction == DOWN ? direction = LEFT : direction = UP;
	else if (_pipe == 'L')
		direction == DOWN ? direction = RIGHT : direction = UP;
}

void dayTen(const bool& isPartTwo)
{
	FileParser	_fileParser("2023\\InputFiles\\inputD10.txt");
	std::string	line;

	std::vector<std::string>	pipelineMap;
	std::vector<std::vector<t_TileType>>		tileMap;
	//std::vector<int>			distanceMap;
	std::string					loopLine;

	bool						endLoop = false;

	t_Direction					direction = LEFT;
	t_Direction					startDirection = LEFT;

	std::vector<t_Pos>			pipePositions;
	t_Pos						pos;
	int							nbPipes = 0;

	int							x = 0;
	int							y = 0;

	bool						isInsideLoop = false;
	std::vector<t_Pos>			insideLoopPos;

	int							finalValue = 0;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	while ((line = _fileParser.readLineToString()) != "")
	{
		pipelineMap.push_back(line);
		tileMap.push_back(std::vector<t_TileType>(line.size(), UNKNOWN));
	}

	while (pipelineMap[y][x] != 'S') // Looking for Start point
	{
		x += 1;
		if (x >= pipelineMap[y].size())
		{
			y += 1;
			x = 0;
		}
	}

	loopLine.push_back(pipelineMap[y][x]);
	pipePositions.push_back(t_Pos{ x, y });
	tileMap[y][x] = PIPE;

	///* VERBOSE
	std::cout << "Starting point found" << std::endl;
	std::cout << "Looking for start direction... ";
	//*/

	if (x - 1 >= 0 && (pipelineMap[y][x - 1] == 'F' || pipelineMap[y][x - 1] == 'L'))
		direction = LEFT;
	else if (x + 1 < pipelineMap[y].size() && (pipelineMap[y][x + 1] == 'J' || pipelineMap[y][x + 1] == '7'))
		direction = RIGHT;
	else if (y - 1 >= 0 && (pipelineMap[y - 1][x] == 'F' || pipelineMap[y - 1][x] == '7'))
		direction = UP;
	else
		direction = DOWN;

	startDirection = direction;

	///* VERBOSE
	std::cout << startDirection << std::endl;
	std::cout << "Running through the loop..." << std::endl;
	//*/

	while (!endLoop)
	{
		switch (direction)
		{
		case LEFT:
			x -= 1;
			break;
		case RIGHT:
			x += 1;
			break;
		case UP:
			y -= 1;
			break;
		case DOWN:
			y += 1;
			break;
		}
		loopLine.push_back(pipelineMap[y][x]);
		pipePositions.push_back(t_Pos{ x, y });
		tileMap[y][x] = PIPE;
		updateDirection(pipelineMap[y][x], direction);

		if (pipelineMap[y][x] == 'S')
		{
			if (direction == UP)
			{
				if (startDirection == LEFT)
					pipelineMap[y][x] = '7';
				else if (startDirection == RIGHT)
					pipelineMap[y][x] = 'F';
				else
					pipelineMap[y][x] = '|';
			}
			else if (direction == DOWN)
			{
				if (startDirection == LEFT)
					pipelineMap[y][x] = 'J';
				else if (startDirection == RIGHT)
					pipelineMap[y][x] = 'L';
				else
					pipelineMap[y][x] = '|';
			}
			else if (direction == LEFT)
			{
				if (startDirection == UP)
					pipelineMap[y][x] = 'L';
				else if (startDirection == DOWN)
					pipelineMap[y][x] = 'F';
				else
					pipelineMap[y][x] = '-';
			}
			else
			{
				if (startDirection == UP)
					pipelineMap[y][x] = 'J';
				else if (startDirection == DOWN)
					pipelineMap[y][x] = '7';
				else
					pipelineMap[y][x] = '-';
			}

			endLoop = true;
			std::cout << "Loop finished. Replacing starting point by " << pipelineMap[y][x] << std::endl;
		}
	}

	if (!isPartTwo)
		finalValue = (int)loopLine.size() / 2;
	else
	{
		for (int y = 0; y < pipelineMap.size(); y++)
		{
			isInsideLoop = false;
			nbPipes = 0;

			std::cout << "Analyze lines : " << y << "/" << pipelineMap.size() << " [";

			for (int x = 0; x < pipelineMap[y].size(); x++)
			{
				std::cout << "#"; // VERBOSE
				if (checkOutsideV2(pipelineMap, pipePositions, t_Pos{ x, y }) && tileMap[y][x] == UNKNOWN)
					tileMap[y][x] = OUTSIDE;
			}
			std::cout << "]" << std::endl; // VERBOSE
		}

		for (int y = 0; y < pipelineMap.size(); y++)
		{
			for (int x = 0; x < pipelineMap[y].size(); x++)
			{
				if (tileMap[y][x] == UNKNOWN)
					tileMap[y][x] = INSIDE;
			}
		}
	}

	///* VERBOSE
	SetConsoleTextAttribute(hConsole, 8);
	for (int y = 0; y < pipelineMap.size(); y++)
	{
		for (int x = 0; x < pipelineMap[y].size(); x++)
		{
			switch (tileMap[y][x])
			{
			case OUTSIDE:
				std::cout << "O";
				break;
			case PIPE:
				std::cout << pipelineMap[y][x];
				break;
			case INSIDE:
				SetConsoleTextAttribute(hConsole, 10);
				std::cout << "I";
				SetConsoleTextAttribute(hConsole, 8);
				finalValue += 1;
				break;
			default:
				std::cout << ".";
				break;
			}
		}
		std::cout << std::endl;
	}
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << "FINAL VALUE = " << finalValue << std::endl;
	//*/
}
