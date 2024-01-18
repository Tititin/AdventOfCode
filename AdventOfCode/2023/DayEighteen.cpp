#include "DayEighteen.h"

unsigned long long int convertHexToDec(const std::string& _lengthHex)
{
	std::string hexKey = "0123456789abcdef";
	unsigned long long int result = 0;

	for (int i = _lengthHex.size() - 1; i >= 0; i--)
	{
		for (int c = 0; c < hexKey.size(); c++)
		{
			if (hexKey[c] == _lengthHex[i])
				result += std::pow(16, _lengthHex.size() - 1 - i) * c;
		}
	}

	return result;
}

void updateDirection(const std::string& _word, t_Direction& _direction)
{
	if (_word == "R")
		_direction = RIGHT;
	else if (_word == "L")
		_direction = LEFT;
	else if (_word == "U")
		_direction = UP;
	else if (_word == "D")
		_direction = DOWN;
}

bool checkLeft(const std::vector<std::string>& _digMap, const t_Pos& _pos)
{
	unsigned int	nbBorderGroups = 0;
	bool			isBorder = false;

	for (int x = _pos.x; x >= 0; x--)
	{
		if (_digMap[_pos.y][x] == '#')
			isBorder = true;
		else if (isBorder)
		{
			isBorder = false;
			nbBorderGroups += 1;
		}
	}

	if (isBorder)
		nbBorderGroups += 1;

	return nbBorderGroups % 2 != 0;
}

bool checkRight(const std::vector<std::string>& _digMap, const t_Pos& _pos)
{
	unsigned int	nbBorderGroups = 0;
	bool			isBorder = false;

	for (int x = _pos.x; x < _digMap[_pos.y].size(); x++)
	{
		if (_digMap[_pos.y][x] == '#')
			isBorder = true;
		else if (isBorder)
		{
			isBorder = false;
			nbBorderGroups += 1;
		}
	}

	if (isBorder)
		nbBorderGroups += 1;

	return nbBorderGroups % 2 != 0;
}

bool checkUp(const std::vector<std::string>& _digMap, const t_Pos& _pos)
{
	unsigned int	nbBorderGroups = 0;
	bool			isBorder = false;

	for (int y = _pos.y; y >= 0; y--)
	{
		if (_digMap[y][_pos.x] == '#')
			isBorder = true;
		else if (isBorder)
		{
			isBorder = false;
			nbBorderGroups += 1;
		}
	}

	if (isBorder)
		nbBorderGroups += 1;

	return nbBorderGroups % 2 != 0;
}

bool checkDown(const std::vector<std::string>& _digMap, const t_Pos& _pos)
{
	unsigned int	nbBorderGroups = 0;
	bool			isBorder = false;

	for (int y = _pos.y; y < _digMap.size(); y++)
	{
		if (_digMap[y][_pos.x] == '#')
			isBorder = true;
		else if (isBorder)
		{
			isBorder = false;
			nbBorderGroups += 1;
		}
	}

	if (isBorder)
		nbBorderGroups += 1;

	return nbBorderGroups % 2 != 0;
}

void dayEighteen(const bool& isPartTwo)
{
	FileParser	_fileParser("2023\\InputFiles\\inputD18.txt");
	std::string	word;

	t_Direction		direction = NONE;

	std::vector<t_Pos>	diggerTiles;
	std::vector<t_Direction>	directions;
	t_Pos				pos;

	bool				isInside = false;

	long long int					x = 0;
	long long int					y = 0;
	long long int					nb = 0;

	unsigned long long int	finalValue = 0;

	std::cout << "Reading file and moves..." << std::endl;
	while ((word = _fileParser.readWordToString()) != "")
	{
		if (!isPartTwo)
			updateDirection(word, direction);

		if (word[0] >= '0' && word[0] <= '9')
		{
			if (!isPartTwo)
			{
				nb = std::stoi(word);
				while (nb != 0)
				{
					diggerTiles.push_back(t_Pos{ x, y });
					directions.push_back(direction);
					if (direction == RIGHT)
						x += 1;
					else if (direction == LEFT)
						x -= 1;
					else if (direction == UP)
						y -= 1;
					else if (direction == DOWN)
						y += 1;
					nb -= 1;
				}
			}
		}
		if (word[0] == '(')
		{
			if (isPartTwo)
			{
				std::string lengthHex = word.substr(2, 5);
				unsigned long long int nbDec = convertHexToDec(lengthHex);

				if (word[7] == '0')
				{
					direction = RIGHT;
					std::cout << "R ";
				}
				else if (word[7] == '1')
				{
					direction = DOWN;
					std::cout << "D ";
				}
				else if (word[7] == '2')
				{
					direction = LEFT;
					std::cout << "L ";
				}
				else
				{
					direction = UP;
					std::cout << "U ";
				}

				std::cout << nbDec << std::endl;

				while (nbDec != 0)
				{
					diggerTiles.push_back(t_Pos{ x, y });
					directions.push_back(direction);
					if (direction == RIGHT)
						x += 1;
					else if (direction == LEFT)
						x -= 1;
					else if (direction == UP)
						y -= 1;
					else if (direction == DOWN)
						y += 1;
					nbDec -= 1;
				}
			}
		}
	}

	x = 0;
	y = 0;
	long long int	minX = 0;
	long long int	minY = 0;

	std::cout << "Calibrating data..." << std::endl;

	for (int i = 0; i < diggerTiles.size(); i++)
	{
		if (diggerTiles[i].x > x)
			x = diggerTiles[i].x;
		if (diggerTiles[i].y > y)
			y = diggerTiles[i].y;
		if (diggerTiles[i].x < minX)
			minX = diggerTiles[i].x;
		if (diggerTiles[i].y < minY)
			minY = diggerTiles[i].y;
	}

	std::vector<std::string>	digMap;
	std::string					digLine;

	if (!isPartTwo)
	{

		std::cout << "Drawing calibrated map..." << std::endl;

		for (long long int i = 0; i <= (x - minX); i++)
			digLine += '.';
		for (long long int i = 0; i <= (y - minY); i++)
			digMap.push_back(digLine);
	}
	if (!isPartTwo)
	{
		std::cout << "Calibrating positions..." << std::endl;

		for (long long int i = 0; i < diggerTiles.size(); i++)
		{
			diggerTiles[i].x -= minX;
			diggerTiles[i].y -= minY;
		}
	}
	if (!isPartTwo)
	{
		std::cout << "Converting starting point into pipe..." << std::endl;

		if ((directions[directions.size() - 1] == RIGHT && directions[0] == UP)
			|| (directions[directions.size() - 1] == DOWN && directions[0] == LEFT))
			digMap[diggerTiles[0].y][diggerTiles[0].x] = 'J';
		else if ((directions[directions.size() - 1] == UP && directions[0] == RIGHT)
			|| (directions[directions.size() - 1] == LEFT && directions[0] == DOWN))
			digMap[diggerTiles[0].y][diggerTiles[0].x] = 'F';
		else if ((directions[directions.size() - 1] == RIGHT && directions[0] == DOWN)
			|| (directions[directions.size() - 1] == UP && directions[0] == LEFT))
			digMap[diggerTiles[0].y][diggerTiles[0].x] = '7';
		else if ((directions[directions.size() - 1] == DOWN && directions[0] == RIGHT)
			|| (directions[directions.size() - 1] == LEFT && directions[0] == UP))
			digMap[diggerTiles[0].y][diggerTiles[0].x] = 'L';
		else
			digMap[diggerTiles[0].y][diggerTiles[0].x] = '#';

		std::cout << "Converting other tiles into pipes..." << std::endl;

		for (int i = 1; i < diggerTiles.size(); i++)
		{
			if (directions[i] == directions[i - 1])
			{
				if (checkIfDirectionIsHorizontal(directions[i]))
					digMap[diggerTiles[i].y][diggerTiles[i].x] = '-';
				else
					digMap[diggerTiles[i].y][diggerTiles[i].x] = '|';
			}
			else
			{
				if ((directions[i] == RIGHT && directions[i - 1] == UP)
					|| (directions[i] == DOWN && directions[i - 1] == LEFT))
					digMap[diggerTiles[i].y][diggerTiles[i].x] = 'F';
				else if ((directions[i] == UP && directions[i - 1] == RIGHT)
					|| (directions[i] == LEFT && directions[i - 1] == DOWN))
					digMap[diggerTiles[i].y][diggerTiles[i].x] = 'J';
				else if ((directions[i] == RIGHT && directions[i - 1] == DOWN)
					|| (directions[i] == UP && directions[i - 1] == LEFT))
					digMap[diggerTiles[i].y][diggerTiles[i].x] = 'L';
				else if ((directions[i] == DOWN && directions[i - 1] == RIGHT)
					|| (directions[i] == LEFT && directions[i - 1] == UP))
					digMap[diggerTiles[i].y][diggerTiles[i].x] = '7';
				else
					digMap[diggerTiles[i].y][diggerTiles[i].x] = '?';
			}
		}

		std::cout << "Starting analysis..." << std::endl;

		for (int y = 0; y < digMap.size(); y++)
		{
			std::cout << "Analyze : " << y << "/" << digMap.size() << " [";
			for (int x = 0; x < digMap[y].size(); x++)
			{
				std::cout << "#";
				if (checkOutsideV2(digMap, diggerTiles, t_Pos{ x, y }) && !checkIfPipeline(diggerTiles, t_Pos{ x, y }))
					digMap[y][x] = '*';
				else
					finalValue += 1;
			}
			std::cout << "]" << std::endl;
		}

		for (int i = 0; i < digMap.size(); i++)
			std::cout << digMap[i] << std::endl;

		std::cout << "PERMIETER = " << diggerTiles.size() << std::endl;
	}
	else
	{
		long long int area = 0;

		for (int i = 1; i < diggerTiles.size(); i++)
			area += diggerTiles[i - 1].x * diggerTiles[i].y - diggerTiles[i - 1].y * diggerTiles[i].x;
		area = abs(area);
		area /= 2;

		finalValue = area + 1 - (diggerTiles.size()) / 2;
		finalValue += diggerTiles.size();
	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}
