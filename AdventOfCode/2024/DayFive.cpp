#include "DayFive.h"

bool checkRules(std::vector<int>& _updates, std::map<int, std::vector<int>>& _rules, const bool& isPartTwo)
{
	bool	areRulesRespected = true;
	bool isSorted = true;

	//std::cout << "UPDATES : ";
	//for (int x = 0; x < _updates.size(); x++)
	//	std::cout << _updates[x] << " ";
	//std::cout << std::endl;

	for (int i = 0; i < _updates.size() && areRulesRespected; i++) // On prend une page après l'autre
	{
		//std::cout << "RULES : ";
		//for (int x = 0; x < _rules[_updates[i]].size(); x++)
		//	std::cout << _rules[_updates[i]][x] << " ";
		//std::cout << std::endl;

		std::vector<int>	tmp = _rules[_updates[i]];

		for (int j = i + 1; j < _updates.size() && areRulesRespected; j++) // Pour chaque page suivant la page en cours, on analyse les pages suivantes, une par une
		{
			for (int k = 0; k < tmp.size() && areRulesRespected; k++) // Pour chaque page analysée, on vérifie si elle respecte les règles
			{
				if (tmp[k] == _updates[j])
				{
					//std::cout << "Error : Forbidden move" << std::endl;
					areRulesRespected = false;
				}
			}
			tmp.clear();
		}
	}

	//std::cout << std::endl;

	if (areRulesRespected && isPartTwo)
		return false;
	else if (isPartTwo)
		return true;
	else
		return areRulesRespected;
}

void dayFive(const bool& isPartTwo)
{
	FileParser	_file("2024\\InputFiles\\inputD5.txt");
	std::string	line;
	unsigned long long int	finalValue = 0;

	std::map<int, std::vector<int>>	pagesRules;
	std::vector<std::vector<int>>	updates;

	while ((line = _file.readLineToString()) != "")
	{
		int pageA = (line[0] - '0') * 10 + (line[1] - '0');
		int pageB = (line[3] - '0') * 10 + (line[4] - '0');
		std::vector<int>	tmpVec;

		if (pagesRules.find(pageB) != pagesRules.end())
		{
			//std::cout << "EXISTING ENTRY FOR PAGE " << pageA << " -> PAGE " << pagesRules[pageA][0] << " SHOULD BE PRINTED BEFORE !" << std::endl;
			pagesRules[pageB].push_back(pageA);
		}
		else
		{
			tmpVec.push_back(pageA);
			pagesRules.insert(std::pair<int, std::vector<int>>(pageB, tmpVec));
			tmpVec.clear();
		}
	}

	while ((line = _file.readLineToString()) != "")
	{
		std::vector<int>	tmp;
		int					nb = 0;

		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] != ',')
				nb = nb * 10 + line[i] - '0';
			else
			{
				tmp.push_back(nb);
				nb = 0;
			}
		}
		tmp.push_back(nb);
		updates.push_back(tmp);
		tmp.clear();
		nb = 0;
	}

	unsigned int	nbFalse = 0;

	for (int i = 0; i < updates.size(); i++)
	{
		if (checkRules(updates[i], pagesRules, isPartTwo))
			finalValue += updates[i][updates[i].size() / 2];
		else
			nbFalse += 1;
	}

	//std::cout << "UPDATE VECTOR SIZE = " << updates.size() << std::endl;

	std::cout << "WRONG UPDATES = " << nbFalse << "/" << updates.size() << std::endl;
	//std::cout << "FINAL VALUE = " << finalValue << std::endl;
}