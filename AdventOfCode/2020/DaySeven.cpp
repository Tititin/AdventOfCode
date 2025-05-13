#include "DaySeven.h"

bool isBagNotInList(const std::vector<std::string>& _bags, const std::string& _bag)
{
	for (int i = 0; i < _bags.size(); i++)
		if (_bags[i] == _bag)
			return false;
	return true;
}

void daySeven(const bool& isPartTwo)
{
	FileParser	_fileParser("2020\\InputFiles\\inputD7bis.txt");
	std::string	line;
	unsigned long long int	finalValue = 0;

	std::queue<std::string>		bagsToSearch;
	std::vector<std::string>	rules;
	std::vector<std::string>	bags;

	bagsToSearch.push("shiny gold");

	while ((line = _fileParser.readLineToString()) != "")
		rules.push_back(line);

	while (!bagsToSearch.empty())
	{
		std::string	bag = bagsToSearch.front();

		for (int i = 0; i < rules.size(); i++)
		{
			std::stringstream	ruleExplorer(rules[i]);
			std::string			bagColorFirst = "";
			std::string			bagColorSecond = "";
			std::string			bagFull = "";
			std::string			bagSubString = "";

			ruleExplorer >> bagColorFirst;
			ruleExplorer >> bagColorSecond;
			bagFull = bagColorFirst + " " + bagColorSecond;

			size_t	pos = rules[i].find("contain");
			bagSubString = rules[i].substr(pos);

			if (bagSubString.find(bag) != std::string::npos)
			{
				if (isBagNotInList(bags, bagFull))
				{
					bagsToSearch.push(bagFull);
					bags.push_back(bagFull);
					finalValue += 1;
				}
			}
		}
		bagsToSearch.pop();
	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}