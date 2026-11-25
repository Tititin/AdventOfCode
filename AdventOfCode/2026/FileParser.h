#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ios>
#include <map>
#include <vector>
#include <Windows.h>

# define INPUT_ROOT "2026//InputFiles//inputD "
# define INPUT_DAY_ONE "2026//InputFiles//inputD1.txt"
# define INPUT_DAY_TWO "2026//InputFiles//inputD2.txt"
# define INPUT_DAY_THREE "2026//InputFiles//inputD3.txt"
# define INPUT_DAY_FOUR "2026//InputFiles//inputD4.txt"
# define INPUT_DAY_FIVE "2026//InputFiles//inputD5.txt"
# define INPUT_DAY_SIX "2026//InputFiles//inputD6.txt"
# define INPUT_DAY_SEVEN "2026//InputFiles//inputD7.txt"
# define INPUT_DAY_EIGHT "2026//InputFiles//inputD8.txt"
# define INPUT_DAY_NINE "2026//InputFiles//inputD9.txt"
# define INPUT_DAY_TEN "2026//InputFiles//inputD10.txt"
# define INPUT_DAY_ELEVEN "2026//InputFiles//inputD11.txt"
# define INPUT_DAY_TWELVE "2026//InputFiles//inputD12.txt"

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

	//std::string	readNextWordToString(const std::string& _line, const char& _separator);

	static bool	checkIsNumber(const std::string& _word);
};

