#include <algorithm>
#include "DayTwelve.h"

static unsigned long long int partTwoDebug = 0;

void dayTwelve(const bool& isPartTwo)
{
	FileParser	_fileParser("2023\\InputFiles\\inputD12.txt");
	std::string	word;

	std::vector<std::string>	springsMap;
	std::vector<std::string>	groups;

	std::vector<std::vector<int>>	springCombinations;

	std::map<int, std::vector<int> >	groupsPerSpringID;
	std::map<int, std::string>					springIDs;

	bool						isFillGroups = false;

	unsigned long long int		firstPartValue = 0;
	unsigned long long int		secondPartValue = 1;
	unsigned long long int		finalValue = 0;

	while ((word = _fileParser.readWordToString()) != "")
	{
		if (!isFillGroups)
			springsMap.push_back(word);
		else
			groups.push_back(word);
		isFillGroups = !isFillGroups;
	}

	for (int i = 0; i < springsMap.size(); i++)
	{
		groupsPerSpringID.insert(std::pair<int, std::vector<int>>(i + 1, retrieveGroups(groups[i])));
		springIDs.insert(std::pair<int, std::string>(i + 1, springsMap[i]));
	}

	int	debug = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (auto& spring : groupsPerSpringID)
	{
		// spring.first -> ID of the spring
		// spring.second -> Vector containing all groups
		// springsIDs[spring.first] -> Gets the string pattern
		SetConsoleTextAttribute(hConsole, 7);
		//if (debug >= 990 && debug < 1000)
		//{
			//if (isPartTwo)
			//	springIDs[spring.first] = changePatternPartTwo(springIDs[spring.first], spring.second);
		std::cout << "ANALYZING SPRING #" << spring.first << "-" << springIDs[spring.first].size() << " -> " << springIDs[spring.first] << " WITH GROUPS -> ";
		displayVector(spring.second);
		int nbGroupsToPlace = spring.second.size() + (springIDs[spring.first].size() - getTotalFilledSquares(spring.second));
		springCombinations = calculateCombinations(nbGroupsToPlace, spring.second.size(), spring.second);
		firstPartValue = calculatePossibleCombinations(springCombinations, springIDs[spring.first], spring.second);
		if (isPartTwo)
		{
			std::string newPattern = "";
			if (springIDs[spring.first][springIDs[spring.first].size() - 1] == '?'
				|| springIDs[spring.first][springIDs[spring.first].size() - 1] == '#')
				newPattern = springIDs[spring.first] + "?";
			else
				newPattern = "?" + springIDs[spring.first];
			//std::string	newPatternTemp = "?" + springIDs[spring.first] + "?";
			int newNbGroups = spring.second.size() + (newPattern.size() - getTotalFilledSquares(spring.second));
			std::vector<std::vector<int>>	newCombinations = calculateCombinations(newNbGroups, spring.second.size(), spring.second);
			secondPartValue = calculatePossibleCombinations(newCombinations, newPattern, spring.second);
			secondPartValue = pow(secondPartValue, 4);
		}
		finalValue = finalValue + firstPartValue * secondPartValue;
		std::cout << std::endl;
		//}
		debug += 1;
	}

	std::cout << "FINAL VALUE = " << finalValue;

	// DEBUG LOOPS
	//for (auto const& x : groupsPerSpring)
	//{
	//	std::cout << "SPRINGS -> " << x.first << std::endl;
	//	std::cout << "GROUPS TO PLACE ->";
	//	for (int val : x.second)
	//		std::cout << " " << val;
	//	std::cout << std::endl << std::endl;
	//}
	//for (int i = 0; i < springsMap.size(); i++)
	//{
	//	std::cout << "SPRINGS -> " << springsMap[i] << std::endl;
	//	std::cout << "GROUPS TO PLACE ->";
	//	for (int j = 0; j < groupsPerSpring[springsMap[i]].size(); j++)
	//		std::cout << " " << groupsPerSpring[springsMap[i]][j];
	//	std::cout << std::endl << std::endl;
	//}
}

void displayVector(const std::vector<int>& _vector)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < _vector.size(); i++)
	{
		if (_vector[i] >= 0)
		{
			if (_vector[i] == 1)
				SetConsoleTextAttribute(hConsole, 10);
			std::cout << 0;
		}
		std::cout << _vector[i] << " ";
		SetConsoleTextAttribute(hConsole, 7);
	}
	std::cout << std::endl;
}

std::string changePatternPartTwo(const std::string& _oldPattern, std::vector<int>& _groups)
{
	std::vector<int>	tmp = _groups;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < tmp.size(); j++)
			_groups.push_back(tmp[j]);
	}
	return std::string(_oldPattern + "?" + _oldPattern + "?" + _oldPattern + "?" + _oldPattern + "?" + _oldPattern);
}

std::vector<std::vector<int>> calculateCombinations(int n, int r, std::vector<int> _groupsSizes)
{
	std::vector<std::vector<int>>	combinations;
	std::vector<int>				elem;

	int								index = 0;

	std::vector<bool> v(n);
	std::fill(v.begin(), v.begin() + r, true);

	do {
		bool isFirstOne = true;
		for (int i = 0; i < n; ++i) {
			if (v[i])
			{
				if (!isFirstOne)
					elem.push_back(-1);
				else
					isFirstOne = false;
				for (int x = 0; x < _groupsSizes[index]; x++)
					elem.push_back(1);
				index += 1;
			}
			else
				elem.push_back(-1);
		}
		combinations.push_back(elem);
		//displayVector(elem);
		if (partTwoDebug % 1000000 == 0)
			std::cout << "ANALYZED " << partTwoDebug << " COMBINATIONS" << std::endl;
		partTwoDebug += 1;
		elem.clear();
		index = 0;
	} while (std::prev_permutation(v.begin(), v.end()));

	//std::cout << "END PERMUTATIONS" << std::endl;

	return combinations;
}

std::vector<int> retrieveGroups(const std::string& _groupStr)
{
	std::vector<int>	groups;
	int					groupVar = 0;

	for (int i = 0; i < _groupStr.size(); i++)
	{
		if (_groupStr[i] == ',')
		{
			groups.push_back(groupVar);
			groupVar = 0;
		}
		else
			groupVar = groupVar * 10 + (_groupStr[i] - 48);
	}
	groups.push_back(groupVar);

	return groups;
}

int getTotalFilledSquares(const std::vector<int>& _groups)
{
	int	value = 0;


	for (int elem : _groups)
		value += elem;

	std::cout << "TOTAL FILLED SQUARES = " << value + _groups.size() - 1 << std::endl;

	return value + _groups.size() - 1;
}

bool isPossibleCombination(const std::vector<int>& _pattern, const std::vector<int>& _combination)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	bool	isCompatible = true;

	//std::cout << "CHECKING IF POSSIBLE COMBINATION" << std::endl;

	for (int i = 0; i < _pattern.size() && isCompatible; i++)
	{
		if ((_pattern[i] == -1 && _combination[i] == 1)
			|| (_pattern[i] == 1 && _combination[i] == -1))
			isCompatible = false;

		if (_pattern[i] == 0)
			SetConsoleTextAttribute(hConsole, 7);
		else if (isCompatible)
			SetConsoleTextAttribute(hConsole, 10);
		else
			SetConsoleTextAttribute(hConsole, 12);

		if (_combination[i] >= 0)
			std::cout << 0 << _combination[i] << " ";
		else
			std::cout << _combination[i] << " ";
	}
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << std::endl;

	return isCompatible;
}

int calculatePossibleCombinations(std::vector<std::vector<int>>& _combinations, const std::string& _pattern, std::vector<int> _groupsSize)
{
	std::vector<int>	numericalPattern;
	bool				isCompatiblePattern = true;

	std::vector<int>::iterator	it;

	int					finalValue = 0;

	//std::cout << "LOOKING FOR POSSIBLE COMBINATIONS" << std::endl;

	for (int i = 0; i < _pattern.size(); i++)
	{
		if (_pattern[i] == '#')
			numericalPattern.push_back(1);
		else if (_pattern[i] == '.')
			numericalPattern.push_back(-1);
		else
			numericalPattern.push_back(0);
	}

	std::cout << "PATTERN CONVERTED TO NUMERICAL FORMAT" << std::endl;
	displayVector(numericalPattern);

	for (int i = 0; i < _combinations.size(); i++)
	{
		/*std::cout << "Fulfilling real square groups" << std::endl;
		std::cout << "FULFILLING COMBINATION -> ";
		displayVector(_combinations[i]);
		for (it = _combinations[i].end() - 1; it > _combinations[i].begin(); it--)
		{
			std::cout << "ITERATOR POINTS AT " << *it << std::endl;
			if (*it == 1)
			{
				int index = it - _combinations[i].begin();
				if (_groupsSize[_groupsSize.size() - 1] > 1)
				{
					_combinations[i].insert(it, _groupsSize[_groupsSize.size() - 1] - 1, 1);
					it = _combinations[i].begin() + index;
				}
				_groupsSize.pop_back();
			}
		}*/
		if (isPossibleCombination(numericalPattern, _combinations[i]))
			finalValue += 1;
	}
	std::cout << "ENTRY RESULT -> " << finalValue << std::endl;

	return finalValue;
}
