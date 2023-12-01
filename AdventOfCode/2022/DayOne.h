#pragma once
#include "Elf.h"
#include "FileParser.h"
#include <vector>

void		dayOne();

const int&	getElfWithMostCalories(const std::vector<Elf>& elves);
const int&	getTopThreeElvesCalories(std::vector<Elf>& elves);