#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ios>
#include <map>
#include <vector>
#include <Windows.h>

typedef enum	e_Direction
{
	NONE = 0,
	LEFT,
	RIGHT,
	UP,
	DOWN
}				t_Direction;

typedef struct	s_Pos
{
	long long int			x = 0;
	long long int			y = 0;
}				t_Pos;

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

