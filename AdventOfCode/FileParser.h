#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ios>

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

	// DAY ONE
	int readLine();

	//DAY TWO
	std::string readMove();
};

