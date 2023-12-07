#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ios>
#include <map>
#include <vector>
#include <Windows.h>

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

	int			readLineToInt();
	std::string	readLineToString();

	int			readWordToInt();
	std::string readWordToString();

	static bool	checkIsNumber(const std::string& _word);
};

