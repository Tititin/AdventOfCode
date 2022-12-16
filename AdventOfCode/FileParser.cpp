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

int FileParser::readLine()
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

std::string FileParser::readMove()
{
	std::string move;

	_fileStream >> move;

	return (move);
}

std::string FileParser::readRucksack()
{
	std::string line;

	std::getline(_fileStream, line);
	return (line);
}

std::string FileParser::getPairSection()
{
	std::string sections;

	_fileStream >> sections;

	return (sections);
}

std::map<int, char> FileParser::readStackEdge()
{
	std::string edgeLine;
	std::map<int, char> edge;

	std::getline(_fileStream, edgeLine);
	for (int i = 0; i < edgeLine.size(); i++)
	{
		if (edgeLine[i] == '[')
		{
			int pos = i / 4;
			
			i += 1;
			edge[pos] = edgeLine[i];
		}
	}
	return (edge);
}

std::string FileParser::readSignal()
{
	return (readRucksack()); // Same behavior
}