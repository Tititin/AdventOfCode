#include "DayFour.h"

std::vector<int>	cutZones(const std::string& section)
{
	std::vector<int> zones;

	if (section != "")
	{
		std::string z1 = section.substr(0, section.find("-"));
		std::string z2 = section.substr(section.find("-") + 1, section.size());

		zones.push_back(std::stoi(z1));
		zones.push_back(std::stoi(z2));
	}

	return (zones);
}

bool checkIfOverlappingZones(const std::vector<int>& section1, const std::vector<int>& section2)
{
	if ((section1[0] >= section2[0] && section1[1] <= section2[1])
		|| (section2[0] >= section1[0] && section2[1] <= section1[1]))
		return (true);
	return (false);
}

void dayFour(bool isPartTwo)
{
	FileParser fileParser("..\\inputD4.txt");
	int ret = 0;

	if (!isPartTwo)
	{
		std::string	pairSections;

		while ((pairSections = fileParser.getPairSection()) != "")
		{
			std::string firstSection = pairSections.substr(0, pairSections.find(","));
			std::string secondSection = pairSections.substr(pairSections.find(",") + 1, pairSections.size());
			
			if (checkIfOverlappingZones(cutZones(firstSection), cutZones(secondSection)))
				ret += 1;
		}

		std::cout << ret << std::endl;
	}
	else
	{

	}
}