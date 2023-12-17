#include "DayFifteen.h"

unsigned int calcBoxNumber(const std::string& _label)
{
	unsigned long int	retValue = 0;

	for (int i = 0; i < _label.size(); i++)
	{
		retValue += _label[i];
		retValue *= 17;
		retValue = retValue % 256;
	}

	return retValue;
}

//void addOrUpdateBoxes(std::map<int, std::vector<t_Lens>>& _boxes, t_Lens& _lens, const int& boxNb)
//{
//	bool	updated = false;
//
//	if (_boxes.find(boxNb) == _boxes.end())
//	{
//		std::vector<t_Lens>	tmp;
//
//		tmp.push_back(_lens);
//
//		_boxes.insert(std::pair<int, std::vector<t_Lens>>(boxNb, tmp));
//	}
//	else
//	{
//		for (int i = 0; i < _boxes[boxNb].size(); i++)
//		{
//			if (_boxes[boxNb][i].label == _lens.label)
//			{
//				_boxes[boxNb][i] = _lens;
//				updated = true;
//			}
//		}
//		if (!updated)
//			_boxes[boxNb].push_back(_lens);
//	}
//}

void addOrUpdateBoxes(std::vector<std::vector<t_Lens>>& _boxes, t_Lens& _lens, const int& boxNb)
{
	bool	isFound = false;

	for (int i = 0; i < _boxes[boxNb].size(); i++)
	{
		if (_boxes[boxNb][i].label == _lens.label)
		{
			_boxes[boxNb][i].focalLength = _lens.focalLength;
			isFound = true;
		}
	}
	if (!isFound)
		_boxes[boxNb].push_back(_lens);
}

//void removeLens(std::map<int, std::vector<t_Lens>>& _boxes, t_Lens& _lens)
//{
//	std::map<int, std::vector<t_Lens>>::iterator	it = _boxes.begin();
//	bool											isFound = false;
//
//	while (it != _boxes.end() && !isFound)
//	{
//		for (int i = 0; i < it->second.size(); i++)
//		{
//			if (it->second[i].label == _lens.label)
//			{
//				t_Lens	tmp = it->second[i];
//				it->second[i] = it->second[it->second.size() - 1];
//				it->second[it->second.size() - 1] = tmp;
//
//				it->second.pop_back();
//
//				//it->second.sw
//			}
//		}
//		it++;
//	}
//}

void removeLens(std::vector<std::vector<t_Lens>>& _boxes, t_Lens& _lens)
{
	bool	isRemoved = false;

	for (int i = 0; i < _boxes.size() && !isRemoved; i++)
	{
		for (int j = 0; j < _boxes[i].size() && !isRemoved; j++)
		{
			if (_boxes[i][j].label == _lens.label)
			{
				while (j < _boxes[i].size() - 1)
				{
					t_Lens	tmp = _boxes[i][j];
					_boxes[i][j] = _boxes[i][j + 1];
					_boxes[i][j + 1] = tmp;

					j += 1;
				}
				_boxes[i].pop_back();
				isRemoved = true;
			}
		}
	}
}

void dayFifteen(const bool& isPartTwo)
{
	FileParser	_fileParser("2023\\InputFiles\\inputD15.txt");
	std::string	line;

	//std::string	lens;
	t_Lens			lens;

	std::map<int, std::vector<t_Lens>>	lensBoxes;
	std::vector<std::vector<t_Lens>>	boxes(256);

	line = _fileParser.readLineToString();

	unsigned long long int	tempValue = 0;
	unsigned long long int	finalValue = 0;

	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] != ',')
		{
			if (!isPartTwo)
			{
				tempValue += line[i];
				tempValue *= 17;
				tempValue = tempValue % 256;
			}
			else
			{
				//std::cout << "COUCOU" << std::endl;
				if (line[i] != '=' && line[i] != '-')
					lens.label += line[i];
				else if (line[i] == '=')
				{
					int boxNb = 0;

					lens.focalLength += line[i + 1] - 48;
					boxNb = calcBoxNumber(lens.label);

					std::cout << "LENS = " << lens.label << " " << lens.focalLength << std::endl; // FOCAL LENGTH IS VERY BROKEN
					std::cout << "BOX = " << boxNb << std::endl << std::endl;

					//if (lensBoxes.find(box))
					//addOrUpdateBoxes(lensBoxes, lens, boxNb);
					addOrUpdateBoxes(boxes, lens, boxNb);
				}
				else
					//removeLens(lensBoxes, lens);
					removeLens(boxes, lens);

			}
		}
		else
		{
			//std::cout << "CURRENT VALUE = " << tempValue << std::endl;
			lens.focalLength = 0;
			lens.label.clear();
			finalValue += tempValue;
			tempValue = 0;
		}
	}
	finalValue += tempValue;


	if (isPartTwo)
	{
		finalValue = 0;
		for (int y = 0; y < boxes.size(); y++)
		{
			if (boxes[y].size() != 0)
			{
				std::cout << "Box " << y << ":";
				for (int x = 0; x < boxes[y].size(); x++)
				{
					std::cout << " [" << boxes[y][x].label << " " << boxes[y][x].focalLength << "]";
					finalValue += (y + 1) * (x + 1) * boxes[y][x].focalLength;
				}
				std::cout << std::endl;
			}
		}
	}
	/*if (isPartTwo)
	{
		for (auto it = lensBoxes.begin(); it != lensBoxes.end(); it++)
		{
			std::cout << "Box " << it->first << ":";
			for (int i = 0; i < it->second.size(); i++)
				std::cout << " [" << it->second[i].label << " " << it->second[i].focalLength << "]";
			std::cout << std::endl;
		}
	}*/

	std::cout << "FINAL VALUE = " << finalValue << std::endl;
}
