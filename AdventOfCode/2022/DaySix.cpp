#include "DaySix.h"

bool checkMarkerValidity(const std::list<char>& marker, const int& requiredLength)
{
	if (marker.size() < requiredLength)
		return (false);

	for (char c : marker)
	{
		auto it = std::find(marker.begin(), marker.end(), c);
		it++;
		while (it != marker.end())
		{
			if (*it == c)
				return (false);
			it++;
		}
	}
	return (true);
}

void daySix(bool isPartTwo)
{
	FileParser fileParser("2022\\InputFiles\\inputD6.txt");
	std::string signal;
	std::list<char> marker;
	int requiredLength;
	int i = 0;
	int ret = 0;

	signal = fileParser.readSignal();

	if (isPartTwo)
		requiredLength = 14;
	else
		requiredLength = 4;

	while (!checkMarkerValidity(marker, requiredLength))
	{
		if (i >= requiredLength)
			marker.pop_front();
		marker.push_back(signal[i]);
		ret += 1;
		i += 1;
	}

	std::cout << ret << std::endl;
}