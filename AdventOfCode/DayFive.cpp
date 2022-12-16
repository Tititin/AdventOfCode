#include "DayFive.h"

void reverseStacks(std::vector<std::vector<char> >& stacks)
{
	for (int x = 0; x < stacks.size(); x++)
	{
		for (int y = 0; y < stacks[x].size() / 2; y++)
		{
			char temp = stacks[x][y];
			stacks[x][y] = stacks[x][stacks[x].size() - 1 - y];
			stacks[x][stacks[x].size() - 1 - y] = temp;
		}
	}
}

void doMove(std::vector<std::vector<char>>& stacks, const t_moveParams& moveParams, bool isPartTwo)
{
	int qty = moveParams.quantity;

	if (!isPartTwo)
	{
		char temp;

		while (qty > 0)
		{
			temp = stacks[moveParams.srcPos][stacks[moveParams.srcPos].size() - 1];
			stacks[moveParams.srcPos].pop_back();
			stacks[moveParams.destPos].push_back(temp);
			qty -= 1;
		}
	}
	else
	{
		std::vector<char> temp;

		while (qty > 0)
		{
			temp.push_back(stacks[moveParams.srcPos][stacks[moveParams.srcPos].size() - 1]);
			stacks[moveParams.srcPos].pop_back();
			qty -= 1;
		}
		while (temp.size() > 0)
		{
			stacks[moveParams.destPos].push_back(temp[temp.size() - 1]);
			temp.pop_back();
		}
	}
}

void dayFive(bool isPartTwo)
{
	FileParser fileParser("..\\inputD5.txt");
	std::vector<std::vector<char> > stacks(9);
	std::map<int, char> edge;

	std::string move;
	t_moveParams moveParams;

	while ((edge = fileParser.readStackEdge()).size() != 0)
	{
		for (int i = 0; i < stacks.size(); i++)
		{
			if (edge.count(i) > 0)
				stacks[i].push_back(edge[i]);
		}
	}

	reverseStacks(stacks);

	while ((move = fileParser.readMove()) != "")
	{
		if (move == "move")
		{
			move = fileParser.readMove();
			moveParams.quantity = std::stoi(move);
		}
		if (move == "from")
		{
			move = fileParser.readMove();
			moveParams.srcPos = std::stoi(move) - 1;
		}
		if (move == "to")
		{
			move = fileParser.readMove();
			moveParams.destPos = std::stoi(move) - 1;
			doMove(stacks, moveParams, isPartTwo);
		}
	}


	for (int x = 0; x < stacks.size(); x++)
	{
		for (int y = 0; y < stacks[x].size(); y++)
			std::cout << stacks[x][y];
		std::cout << std::endl;
	}
}