#include "DayTwentyTwo.h"

t_Brick createBrick(const t_Point& _start, const t_Point& _end)
{
	t_Brick	brick;

	if (_start.z != _end.z)
		brick = createVerticalBrick(_start, _end);
	else if (_start.x == _end.x)
		brick = createHorizontalYBrick(_start, _end);
	else if (_start.y == _end.y)
		brick = createHorizontalXBrick(_start, _end);

	if (_start.z == _end.z || _start.z < _end.z)
		brick.z = _start.z;
	else
		brick.z = _end.z;

	return brick;
}

t_Brick createHorizontalYBrick(const t_Point& _start, const t_Point& _end)
{
	t_Brick brick;
	int		direction = 0;
	t_Point	point;

	if (_end.y >= _start.y)
		direction = 1;
	else
		direction = -1;

	point = _start;
	while (point.y != _end.y)
	{
		std::cout << "c";
		brick.coorXY.push_back(t_BrickCoorXY{ point.x, point.y });
		point.y += direction;
	}
	brick.coorXY.push_back(t_BrickCoorXY{ point.x, point.y });

	return brick;
}

t_Brick createVerticalBrick(const t_Point& _start, const t_Point& _end)
{
	t_Brick	brick;
	int		direction = 0;
	t_Point	point;

	if (_end.z >= _start.z)
		direction = 1;
	else
		direction = -1;

	point = _start;
	while (point.z != _end.z)
	{
		std::cout << "a";
		brick.coorXY.push_back(s_BrickCoorXY{ point.x, point.y });
		point.z += direction;
	}
	brick.coorXY.push_back(s_BrickCoorXY{ point.x, point.y });

	return brick;
}

t_Brick createHorizontalXBrick(const t_Point& _start, const t_Point& _end)
{
	t_Brick brick;
	int		direction = 0;
	t_Point	point;

	if (_end.x >= _start.x)
		direction = 1;
	else
		direction = -1;

	point = _start;
	while (point.x != _end.x)
	{
		std::cout << "b";
		brick.coorXY.push_back(t_BrickCoorXY{ point.x, point.y });
		point.x += direction;
	}
	brick.coorXY.push_back(t_BrickCoorXY{ point.x, point.y });

	return brick;
}

void moveBelow(t_Brick& brick)
{
	brick.z -= 1;
}

void dayTwentyTwo(const bool& isPartTwo)
{
	FileParser				_fileParser("2023\\InputFiles\\inputD22bis.txt");
	std::string				line;
	t_Brick					brick;
	int						brickID = 0;
	std::vector<t_Brick>	brickArray;

	while ((line = _fileParser.readLineToString()) != "")
	{
		t_Point	startPoint;
		t_Point	endPoint;
		int		axis = 0;
		bool	isStartPoint = true;

		for (int i = 0; i < line.size(); i++)
		{
			while (i < line.size() && (line[i] != ',' && line[i] != '~'))
			{
				if (isStartPoint)
				{

					if (axis == 0)
						startPoint.x = startPoint.x * 10 + (line[i] - 48);
					else if (axis == 1)
						startPoint.y = startPoint.y * 10 + (line[i] - 48);
					else
						startPoint.z = startPoint.z * 10 + (line[i] - 48);
				}
				else
				{
					if (axis == 0)
						endPoint.x = endPoint.x * 10 + (line[i] - 48);
					else if (axis == 1)
						endPoint.y = endPoint.y * 10 + (line[i] - 48);
					else
						endPoint.z = endPoint.z * 10 + (line[i] - 48);
				}
				i += 1;
			}
			if (line[i] == ',')
				axis = (axis + 1) % 3;
			else if (line[i] == '~')
			{
				axis = 0;
				isStartPoint = false;
			}
		}
		/*std::cout << "START POINT -> " << startPoint.x << ";" << startPoint.y << ";" << startPoint.z << std::endl;*/
		/*std::cout << "END POINT -> " << endPoint.x << ";" << endPoint.y << ";" << endPoint.z << std::endl;*/
		brick = createBrick(startPoint, endPoint);
		brick.id = brickID++;
		brickArray.push_back(brick);
		/*std::cout << "--- BRICK Z = " << brick.z << " ---" << std::endl;*/
	}

	/*for (int i = 0; i < brickArray.size(); i++)
	{
		std::cout << "==========" << std::endl;
		std::cout << "BRICK " << brickArray[i].id << std::endl;
		std::cout << "BRICK DATA : " << brickArray[i].coorXY.size() << " // " << brickArray[i].z << std::endl;
		std::cout << "==========" << std::endl;
		std::cout << std::endl;
	}*/
}
