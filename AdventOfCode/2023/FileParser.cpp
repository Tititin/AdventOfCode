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

	while (std::getline(_fileStream, line))
		return (line);
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
	std::string move;

	_fileStream >> move;

	return (move);
}
