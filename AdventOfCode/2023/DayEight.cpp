#include "DayEight.h"

unsigned long long int calcPPCM(unsigned long long int& x, unsigned long long int& y)
{
	unsigned long long int	a = x;
	unsigned long long int	b = y;

	if (x == 1)
		return (y);

	while (a != b)
	{
		while (a > b)
			b += y;
		while (a < b)
			a += x;
	}
	return a;
}

bool checkIDs(const std::vector<int>& _ids, const std::vector<t_Room>& _rooms)
{
	bool	isCorrect = true;

	for (int i = 0; i < _ids.size(); i++)
	{
		if (_rooms[_ids[i]].name[2] != 'Z')
			return false;
	}
	return true;
}

bool checkIDs(const int& _id, const std::vector<int>& _ends)
{
	for (int i = 0; i < _ends.size(); i++)
	{
		if (_id == _ends[i])
			return true;
	}
	return false;
}

void dayEight(const bool& isPartTwo)
{
	FileParser			_fileParser("2023\\InputFiles\\inputD8.txt");
	std::string			word;

	std::vector<t_Room>	rooms;
	t_Room				tmp;
	std::string			instructions;

	std::map<std::string, int>	roomsIDs;
	int							id = 0; // PART ONE
	std::vector<int>			IDs; // PART TWO
	std::vector<int>			endIDs;

	std::vector<unsigned long long int>	nbStepsByPath;
	unsigned long long int	steps = 0;

	unsigned long long int	finalValue = 0;

	instructions = _fileParser.readWordToString();

	while ((word = _fileParser.readWordToString()) != "")
	{
		tmp.name = word;

		word = _fileParser.readWordToString();
		word = _fileParser.readWordToString();

		tmp.left = word.substr(1, 3);

		word = _fileParser.readWordToString();

		tmp.right = word.substr(0, 3);

		rooms.push_back(tmp);
		roomsIDs.insert(std::pair<std::string, int>(tmp.name, id));
		id += 1;
	}

	if (!isPartTwo)
	{
		id = roomsIDs["AAA"];

		while (id != roomsIDs["ZZZ"])
		{
			if (instructions[finalValue % instructions.size()] == 'L')
				id = roomsIDs[rooms[id].left];
			else
				id = roomsIDs[rooms[id].right];
			finalValue += 1;
		}
	}
	else
	{
		for (int i = 0; i < rooms.size(); i++)
		{
			if (rooms[i].name[2] == 'A')
				IDs.push_back(roomsIDs[rooms[i].name]);
			else if (rooms[i].name[2] == 'Z')
				endIDs.push_back(roomsIDs[rooms[i].name]);
		}

		finalValue = 1;

		for (int i = 0; i < IDs.size(); i++)
		{
			id = IDs[i];
			std::cout << "ANALYZE PATH " << i << std::endl;
			while (!checkIDs(id, endIDs))
			{
				if (instructions[steps % instructions.size()] == 'L')
					id = roomsIDs[rooms[id].left];
				else
					id = roomsIDs[rooms[id].right];
				steps += 1;
			}
			std::cout << "END PATH " << i << " WITH " << steps << " STEPS !" << std::endl;
			finalValue = calcPPCM(finalValue, steps);
			steps = 0;
		}
		std::cout << std::endl;
	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}
