#include "DayOne.h"

const int& getElfWithMostCalories(const std::vector<Elf>& elves)
{
	int nbCalories = 0;

	for (int i = 0; i < elves.size(); i++)
	{
		if (nbCalories < elves[i].getCalories())
			nbCalories = elves[i].getCalories();
	}

	return (nbCalories);
}

const int& getTopThreeElvesCalories(std::vector<Elf>& elves)
{
	bool isSorted = false;
	int temp = 0;

	while (!isSorted)
	{
		isSorted = true;
		for (int i = 0; i < elves.size() - 1; i++)
		{
			if (elves[i].getCalories() < elves[i + 1].getCalories())
			{
				isSorted = false;
				temp = elves[i].getCalories();
				elves[i].setCalories(elves[i + 1].getCalories());
				elves[i + 1].setCalories(temp);
			}
		}
	}

	temp = 0;

	for (int i = 0; i < 3 && i < elves.size(); i++)
		temp += elves[i].getCalories();

	return (temp);
}

void dayOne()
{
	std::vector<Elf> elves;
	FileParser fileParser("2022\\InputFiles\\inputD1.txt");
	int nb = 0;
	int nbCalories = 0;
	Elf elf;

	while ((nb = fileParser.readLine()) != -1)
	{
		if (nb == -2)
		{
			elves.push_back(Elf(nbCalories));
			nbCalories = 0;
		}
		else
			nbCalories += nb;
	}

	// DAY ONE
	//nbCalories = getElfWithMostCalories(elves);		// D1-1
	nbCalories = getTopThreeElvesCalories(elves);		// D1-2
	std::cout << nbCalories << std::endl;
}