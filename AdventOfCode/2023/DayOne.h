#pragma once

#ifndef DAYONE_H_
# define DAYONE_H_

#include "FileParser.h"

std::vector<std::string>	initNumbersArray();

int							convertLineToCalibrationValue(std::string& line, const bool &isPartTwo = false);

void						dayOne(const bool &isPartTwo = false);

#endif // !DAYONE_H_
