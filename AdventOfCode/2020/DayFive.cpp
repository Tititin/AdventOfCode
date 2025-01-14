#include "DayFive.h"

void dayFive(const bool& isPartTwo)
{
	FileParser	_file("2020\\InputFiles\\inputD5.txt");
	std::string	line;
	unsigned long long int	finalValue = 0;

	std::string				row;
	std::string				column;

	unsigned int			rowNumber = 0;
	unsigned int			columnNumber = 0;

	std::vector<int>		takenSeats;

	while ((line = _file.readLineToString()) != "")
	{
		row = line.substr(0, 7);
		column = line.substr(7, 3);

		for (int i = 0; i < row.size(); i++)
		{
			rowNumber = rowNumber << 1;
			if (row[i] == 'B')
				rowNumber += 1;
		}
		for (int i = 0; i < column.size(); i++)
		{
			columnNumber = columnNumber << 1;
			if (column[i] == 'R')
				columnNumber += 1;
		}

		int seatID = rowNumber * 8 + columnNumber;

		if (finalValue < seatID)
			finalValue = seatID;

		if (isPartTwo)
			takenSeats.push_back(seatID);

		if (isPartTwo)
		{
			sortVector(takenSeats);

			for (int i = 0; i < takenSeats.size() - 1; i++)
				if (takenSeats[i + 1] == takenSeats[i] + 2)
					finalValue = takenSeats[i] + 1;
		}

		rowNumber = 0;
		columnNumber = 0;
	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}