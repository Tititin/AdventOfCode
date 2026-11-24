#include "FileParser.h"

FileParser::FileParser()
{

}

FileParser::FileParser(const std::string& fileName)
{
	_fileName = fileName;
	_fileStream.open(_fileName.c_str(), std::fstream::in);
}

FileParser::~FileParser()
{
	_fileStream.close();
}

bool FileParser::openFile(const std::string& fileName)
{
	_fileName = fileName;
	_fileStream.open(_fileName.c_str(), std::fstream::in);

	if (!_fileStream.is_open())
		std::cerr << "ERROR : FILE " << fileName << " COULDN'T BE OPENED !" << std::endl;
	
	return (_fileStream.is_open());
}

bool FileParser::closeFile()
{
	_fileStream.close();

	return (!_fileStream.is_open());
}

int FileParser::readLineToInt()
{
	int ret;
	std::string line;

	while (std::getline(_fileStream, line))
	{
		if (line == "")
			return (-2);
		else
		{
			ret = std::stoi(line);
			return (ret);
		}
	}
	return (-1);
}

std::string FileParser::readLineToString()
{
	std::string line;

	std::getline(_fileStream, line);

	return (line);
}

int FileParser::readWordToInt()
{
	int number;

	_fileStream >> number;

	return (number);
}

std::string FileParser::readWordToString()
{
	std::string word;

	_fileStream >> word;

	return (word);
}

//std::string FileParser::readNextWordToString(const std::string& _line, const char& _separator)
//{
//	static size_t	currentPos = -1;
//	size_t			endWordPos = _line.find(_separator, currentPos);
//
//	std::string		word = _line.substr(currentPos + 1, endWordPos - currentPos + 1);
//
//	if (currentPos == std::string::npos)
//		return ("");
//
//	currentPos = endWordPos;
//
//	return (word);
//}

bool FileParser::checkIsNumber(const std::string& _word)
{
	for (int i = 0; i < _word.size(); i++)
	{
		if (_word[i] < '0' || _word[i] > '9')
			return false;
	}
	return true;
}
