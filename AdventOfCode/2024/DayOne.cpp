#include "DayOne.h"

void sortVector(std::vector<int>& list, const t_Order& _order)
{
	switch (_order)
	{
	case ASC:
		sortVectorAsc(list);
		break;
	case DESC:
		sortVectorDesc(list);
		break;
	}
}

void sortVectorAsc(std::vector<int>& list)
{
	bool			isSorted = false;
	unsigned int	tmp;

	while (!isSorted)
	{
		isSorted = true;

		for (int i = 0; i < list.size() - 1 && isSorted; i++)
		{
			if (list[i] > list[i + 1])
			{
				isSorted = false;
				tmp = list[i];
				list[i] = list[i + 1];
				list[i + 1] = tmp;
			}
		}
	}
}

void sortVectorDesc(std::vector<int>& list)
{
	bool			isSorted = false;
	unsigned int	tmp;

	while (!isSorted)
	{
		isSorted = true;

		for (int i = 0; i < list.size() - 1 && isSorted; i++)
		{
			if (list[i] < list[i + 1])
			{
				isSorted = false;
				tmp = list[i];
				list[i] = list[i + 1];
				list[i + 1] = tmp;
			}
		}
	}
}

unsigned int findOccurences(const int& _number, const std::vector<int>& _list)
{
	unsigned int	occurences = 0;

	for (int i = 0; i < _list.size(); i++)
	{
		if (_list[i] == _number)
			occurences += 1;
	}

	return (occurences);
}

void dayOne(const bool& isPartTwo)
{
	FileParser	_file("2024\\InputFiles\\inputD1.txt");
	std::string	word;
	unsigned long int finalValue = 0;

	std::vector<int>	listA;
	std::vector<int>	listB;
	bool						isListA = true;
	int				number;

	while ((word = _file.readWordToString()) != "")
	{
		number = std::stoi(word);

		if (isListA)
			listA.push_back(number);
		else
			listB.push_back(number);

		isListA = !isListA;
	}

	if (!isPartTwo)
	{
		sortVector(listA, ASC);
		sortVector(listB, ASC);

		for (int i = 0; i < listA.size(); i++)
			finalValue += abs(listA[i] - listB[i]);
	}
	else
	{
		for (int i = 0; i < listA.size(); i++)
			finalValue += listA[i] * findOccurences(listA[i], listB);
	}


	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}