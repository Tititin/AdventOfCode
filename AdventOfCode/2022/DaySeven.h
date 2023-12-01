#pragma once

#include "FileParser.h"
#include "Directory.h"
#include "File.h"
#include <vector>

void daySeven(bool isPartTwo = false);

void execCd(Directory* *current, std::string& cmdArg);
int execLs(Directory* *current, FileParser& fileParser);

bool isDirectoryAlreadyExists(Directory* parent, const std::string& child);
bool isFilealreadyExists(Directory* parent, const std::string& file);

std::vector<int> sortDirSizes(std::map<int, int>& dirSizes);