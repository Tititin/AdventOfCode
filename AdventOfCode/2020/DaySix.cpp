#include "DaySix.h"

void daySix(const bool& isPartTwo)
{
	FileParser	_file("2020\\InputFiles\\inputD6.txt");
	std::string	line;
	unsigned long long int	finalValue = 0;

	bool	isEndOfFile = false;
	bool	isGroupReady = false;

	std::string	questions = "";
	std::vector<std::string>	questionsGroup;
	std::vector<unsigned int>	yesAnswers(26, 0);

	while (!isEndOfFile)
	{
		line = _file.readLineToString();

		if (line != "")
		{
			isGroupReady = false;

			if (!isPartTwo)
			{
				for (int i = 0; i < line.size(); i++)
					if (questions.find(line[i]) == std::string::npos)
						questions += line[i];
			}
			else
				questionsGroup.push_back(line);
		}
		else if (!isGroupReady)
		{
			isGroupReady = true;

			if (!isPartTwo)
				finalValue += questions.size();
			else
			{
				for (int i = 0; i < questionsGroup.size(); i++)
				{
					for (int j = 0; j < questionsGroup[i].size(); j++)
						yesAnswers[questionsGroup[i][j] - 'a'] += 1;
				}
				for (int i = 0; i < yesAnswers.size(); i++)
					if (yesAnswers[i] == questionsGroup.size())
						finalValue += 1;
			}
			questions.clear();
			questionsGroup.clear();
			for (int i = 0; i < yesAnswers.size(); i++)
				yesAnswers[i] = 0;
		}
		else
			isEndOfFile = true;
	}

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}