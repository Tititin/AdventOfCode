#include "DaySixteen.h"

// NOTE :	Algo is good, but... on a giant maze it causes a stack overflow due to too much recursivity.
//			Maybe try to use some kind of chunks ?
//			Or... Try to concentrate on nodes, maybe ? (Nodes are points in the maze where we can start multiple paths)
//			Let's use the notebook on a smaller maze for the second idea
//			Brainstorm tomorrow

void runMaze(t_MazeRunner _runner, const std::vector<std::string>& _maze, std::vector<std::vector<long int>>& _distances)
{
	unsigned long int	currentDistance;

		_distances[_runner.currentPos.y][_runner.currentPos.x] = _runner.moveMalus;
	currentDistance = _distances[_runner.currentPos.y][_runner.currentPos.x];

	//std::cout << "==========" << std::endl;
	//std::cout << "MAZE CURRENT POS : " << _runner.currentPos.x << ";" << _runner.currentPos.y << std::endl;
	//std::cout << "MAZE CURRENT DISTANCE : " << _distances[_runner.currentPos.y][_runner.currentPos.x] << std::endl;
	//std::cout << std::endl;

	if (_runner.currentPos != _runner.endToReach)
	{
		switch (_runner.currentDirection)
		{
		case RIGHT:
			if (_runner.currentPos.y - 1 >= 0 && _distances[_runner.currentPos.y - 1][_runner.currentPos.x] != -2 && (_distances[_runner.currentPos.y - 1][_runner.currentPos.x] == -1 || _distances[_runner.currentPos.y][_runner.currentPos.x] + 1001 < _distances[_runner.currentPos.y - 1][_runner.currentPos.x]))
				runMaze(t_MazeRunner{ t_Pos{_runner.currentPos.x, _runner.currentPos.y - 1}, UP, 1001 + currentDistance, _runner.endToReach }, _maze, _distances);
			if (_runner.currentPos.x + 1 < _maze[_runner.currentPos.y].size() && _distances[_runner.currentPos.y][_runner.currentPos.x + 1] != -2 && (_distances[_runner.currentPos.y][_runner.currentPos.x + 1] == -1 || _distances[_runner.currentPos.y][_runner.currentPos.x] + 1 < _distances[_runner.currentPos.y][_runner.currentPos.x + 1]))
				runMaze(t_MazeRunner{ t_Pos{_runner.currentPos.x + 1, _runner.currentPos.y}, RIGHT, 1 + currentDistance, _runner.endToReach }, _maze, _distances);
			if (_runner.currentPos.y + 1 < _maze.size() && _distances[_runner.currentPos.y + 1][_runner.currentPos.x] != -2 && (_distances[_runner.currentPos.y + 1][_runner.currentPos.x] == -1 || _distances[_runner.currentPos.y][_runner.currentPos.x] + 1001 < _distances[_runner.currentPos.y + 1][_runner.currentPos.x]))
				runMaze(t_MazeRunner{ t_Pos{_runner.currentPos.x, _runner.currentPos.y + 1}, DOWN, 1001 + currentDistance, _runner.endToReach }, _maze, _distances);
			if (_runner.currentPos.x - 1 >= 0 && _distances[_runner.currentPos.y][_runner.currentPos.x - 1] != -2 && (_distances[_runner.currentPos.y][_runner.currentPos.x - 1] == -1 || _distances[_runner.currentPos.y][_runner.currentPos.x] + 1001 < _distances[_runner.currentPos.y][_runner.currentPos.x - 1]))
				runMaze(t_MazeRunner{ t_Pos{_runner.currentPos.x - 1, _runner.currentPos.y}, LEFT, 1001 + currentDistance, _runner.endToReach }, _maze, _distances);
			break;

		case LEFT:
			if (_runner.currentPos.y - 1 >= 0 && _distances[_runner.currentPos.y - 1][_runner.currentPos.x] != -2 && (_distances[_runner.currentPos.y - 1][_runner.currentPos.x] == -1 || _distances[_runner.currentPos.y][_runner.currentPos.x] + 1001 < _distances[_runner.currentPos.y - 1][_runner.currentPos.x]))
				runMaze(t_MazeRunner{ t_Pos{_runner.currentPos.x, _runner.currentPos.y - 1}, UP, 1001 + currentDistance, _runner.endToReach }, _maze, _distances);
			if (_runner.currentPos.x + 1 < _maze[_runner.currentPos.y].size() && _distances[_runner.currentPos.y][_runner.currentPos.x + 1] != -2 && (_distances[_runner.currentPos.y][_runner.currentPos.x + 1] == -1 || _distances[_runner.currentPos.y][_runner.currentPos.x] + 1001 < _distances[_runner.currentPos.y][_runner.currentPos.x + 1]))
				runMaze(t_MazeRunner{ t_Pos{_runner.currentPos.x + 1, _runner.currentPos.y}, RIGHT, 1001 + currentDistance, _runner.endToReach }, _maze, _distances);
			if (_runner.currentPos.y + 1 < _maze.size() && _distances[_runner.currentPos.y + 1][_runner.currentPos.x] != -2 && (_distances[_runner.currentPos.y + 1][_runner.currentPos.x] == -1 || _distances[_runner.currentPos.y][_runner.currentPos.x] + 1001 < _distances[_runner.currentPos.y + 1][_runner.currentPos.x]))
				runMaze(t_MazeRunner{ t_Pos{_runner.currentPos.x, _runner.currentPos.y + 1}, DOWN, 1001 + currentDistance, _runner.endToReach }, _maze, _distances);
			if (_runner.currentPos.x - 1 >= 0 && _distances[_runner.currentPos.y][_runner.currentPos.x - 1] != -2 && (_distances[_runner.currentPos.y][_runner.currentPos.x - 1] == -1 || _distances[_runner.currentPos.y][_runner.currentPos.x] + 1 < _distances[_runner.currentPos.y][_runner.currentPos.x - 1]))
				runMaze(t_MazeRunner{ t_Pos{_runner.currentPos.x - 1, _runner.currentPos.y}, LEFT, 1 + currentDistance, _runner.endToReach }, _maze, _distances);
			break;

		case UP:
			if (_runner.currentPos.y - 1 >= 0 && _distances[_runner.currentPos.y - 1][_runner.currentPos.x] != -2 && (_distances[_runner.currentPos.y - 1][_runner.currentPos.x] == -1 || _distances[_runner.currentPos.y][_runner.currentPos.x] + 1 < _distances[_runner.currentPos.y - 1][_runner.currentPos.x]))
				runMaze(t_MazeRunner{ t_Pos{_runner.currentPos.x, _runner.currentPos.y - 1}, UP, 1 + currentDistance, _runner.endToReach }, _maze, _distances);
			if (_runner.currentPos.x + 1 < _maze[_runner.currentPos.y].size() && _distances[_runner.currentPos.y][_runner.currentPos.x + 1] != -2 && (_distances[_runner.currentPos.y][_runner.currentPos.x + 1] == -1 || _distances[_runner.currentPos.y][_runner.currentPos.x] + 1001 < _distances[_runner.currentPos.y][_runner.currentPos.x + 1]))
				runMaze(t_MazeRunner{ t_Pos{_runner.currentPos.x + 1, _runner.currentPos.y}, RIGHT, 1001 + currentDistance, _runner.endToReach }, _maze, _distances);
			if (_runner.currentPos.y + 1 < _maze.size() && _distances[_runner.currentPos.y + 1][_runner.currentPos.x] != -2 && (_distances[_runner.currentPos.y + 1][_runner.currentPos.x] == -1 || _distances[_runner.currentPos.y][_runner.currentPos.x] + 1001 < _distances[_runner.currentPos.y + 1][_runner.currentPos.x]))
				runMaze(t_MazeRunner{ t_Pos{_runner.currentPos.x, _runner.currentPos.y + 1}, DOWN, 1001 + currentDistance, _runner.endToReach }, _maze, _distances);
			if (_runner.currentPos.x - 1 >= 0 && _distances[_runner.currentPos.y][_runner.currentPos.x - 1] != -2 && (_distances[_runner.currentPos.y][_runner.currentPos.x - 1] == -1 || _distances[_runner.currentPos.y][_runner.currentPos.x] + 1001 < _distances[_runner.currentPos.y][_runner.currentPos.x - 1]))
				runMaze(t_MazeRunner{ t_Pos{_runner.currentPos.x - 1, _runner.currentPos.y}, LEFT, 1001 + currentDistance, _runner.endToReach }, _maze, _distances);
			break;

		case DOWN:
			if (_runner.currentPos.y - 1 >= 0 && _distances[_runner.currentPos.y - 1][_runner.currentPos.x] != -2 && (_distances[_runner.currentPos.y - 1][_runner.currentPos.x] == -1 || _distances[_runner.currentPos.y][_runner.currentPos.x] + 1001 < _distances[_runner.currentPos.y - 1][_runner.currentPos.x]))
				runMaze(t_MazeRunner{ t_Pos{_runner.currentPos.x, _runner.currentPos.y - 1}, UP, 1001 + currentDistance, _runner.endToReach }, _maze, _distances);
			if (_runner.currentPos.x + 1 < _maze[_runner.currentPos.y].size() && _distances[_runner.currentPos.y][_runner.currentPos.x + 1] != -2 && (_distances[_runner.currentPos.y][_runner.currentPos.x + 1] == -1 || _distances[_runner.currentPos.y][_runner.currentPos.x] + 1001 < _distances[_runner.currentPos.y][_runner.currentPos.x + 1]))
				runMaze(t_MazeRunner{ t_Pos{_runner.currentPos.x + 1, _runner.currentPos.y}, RIGHT, 1001 + currentDistance, _runner.endToReach }, _maze, _distances);
			if (_runner.currentPos.y + 1 < _maze.size() && _distances[_runner.currentPos.y + 1][_runner.currentPos.x] != -2 && (_distances[_runner.currentPos.y + 1][_runner.currentPos.x] == -1 || _distances[_runner.currentPos.y][_runner.currentPos.x] + 1 < _distances[_runner.currentPos.y + 1][_runner.currentPos.x]))
				runMaze(t_MazeRunner{ t_Pos{_runner.currentPos.x, _runner.currentPos.y + 1}, DOWN, 1 + currentDistance, _runner.endToReach }, _maze, _distances);
			if (_runner.currentPos.x - 1 >= 0 && _distances[_runner.currentPos.y][_runner.currentPos.x - 1] != -2 && (_distances[_runner.currentPos.y][_runner.currentPos.x - 1] == -1 || _distances[_runner.currentPos.y][_runner.currentPos.x] + 1001 < _distances[_runner.currentPos.y][_runner.currentPos.x - 1]))
				runMaze(t_MazeRunner{ t_Pos{_runner.currentPos.x - 1, _runner.currentPos.y}, LEFT, 1001 + currentDistance, _runner.endToReach }, _maze, _distances);
			break;
		}
	}
}

void daySixteen(const bool& isPartTwo)
{
	FileParser	_file("2024\\InputFiles\\inputD16.txt");
	std::string	line;
	unsigned long long int	finalValue = 0;

	std::vector<std::string>	mazeMap;
	std::vector<std::vector<long int>>		mazeDistances;

	t_Pos						mazeStart;
	t_Pos						mazeEnd;

	t_MazeRunner				runner;

	// Parse file into a maze map
	while ((line = _file.readLineToString()) != "")
	{
		mazeMap.push_back(line);
		mazeDistances.push_back(std::vector<long int>(line.size(), -2));
	}

	// Getting Start and End + initializing distances map
	for (int y = 0; y < mazeMap.size(); y++)
	{
		for (int x = 0; x < mazeMap[y].size(); x++)
		{
			if (mazeMap[y][x] == 'E')
			{
				mazeEnd.x = x;
				mazeEnd.y = y;
				mazeDistances[y][x] = -1;
			}
			else if (mazeMap[y][x] == 'S')
			{
				mazeStart.x = x;
				mazeStart.y = y;
				mazeDistances[y][x] = 0;
			}
			else if (mazeMap[y][x] == '.')
				mazeDistances[y][x] = -1;
		}
	}

	// Initialize runner
	runner.currentPos = mazeStart;
	runner.endToReach = mazeEnd;

	// Launching maze runner
	runMaze(runner, mazeMap, mazeDistances);

	// Getting final result
	finalValue = mazeDistances[mazeEnd.y][mazeEnd.x];

	// Displaying final result
	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}
