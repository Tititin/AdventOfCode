#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ios>
#include <map>

class FileParser
{
public:
	FileParser();
	FileParser(const std::string& fileName);
	~FileParser();

private:
	std::string _fileName;
	std::ifstream _fileStream;

public:
	bool openFile(const std::string& fileName);
	bool closeFile();

	// DAY 1
	int readLine();

	//DAY 2,5
	std::string readMove();

	//DAY 3
	std::string readRucksack();

	//DAY 4
	std::string getPairSection();

	//DAY 5
	std::map<int, char> readStackEdge();
};

