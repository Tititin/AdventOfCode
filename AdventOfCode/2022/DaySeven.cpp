#include "DaySeven.h"

void execCd(Directory** current, std::string& cmdArg)
{
	if (cmdArg == "..")
	{
		if ((*current)->getName() != "/")
			(*current) = (*current)->getParentDirectory();
		return;
	}
	for (Directory* dir : (*current)->getChildDirectories())
	{
		if (dir->getName() == cmdArg)
		{
			(*current) = dir;
			return;
		}
	}
}

bool isDirectoryAlreadyExists(Directory* parent, const std::string& child)
{
	for (Directory* dir : parent->getChildDirectories())
	{
		if (dir->getName() == child)
			return (true);
	}
	return (false);
}

bool isFilealreadyExists(Directory* parent, const std::string& file)
{
	for (File* f : parent->getFiles())
	{
		if (f->getName() == file)
			return (true);
	}
	return (false);
}

std::vector<int> sortDirSizes(std::map<int, int>& dirSizes)
{
	bool isSorted = false;
	std::vector<int> sorted;
	int i = 0;

	for (std::map<int, int>::iterator it = dirSizes.begin(); it != dirSizes.end(); it++)
		sorted.push_back(it->second);

	while (!isSorted)
	{
		isSorted = true;
		for (int i = 0; i < sorted.size() - 1; i++)
		{
			if (sorted[i] > sorted[i + 1])
			{
				isSorted = false;

				int temp = sorted[i];
				sorted[i] = sorted[i + 1];
				sorted[i + 1] = temp;
			}
		}
	}

	return (sorted);
}

void daySeven(bool isPartTwo)
{
	FileParser fileParser("2022\\InputFiles\\inputD7.txt");
	std::string cmdLine;
	std::string cmd;
	std::string cmdArg;

	Directory* rootDir = new Directory("/");
	Directory* currentDir = rootDir;

	std::string partOne = ".";
	std::string partTwo = ".";

	std::map<int, int> dirSizes;
	std::vector<int> sortedSizes;

	int totalSize = 0;

	int dirId = 0;

	while ((cmdLine = fileParser.readSignal()) != "")
	{
		if (cmdLine[0] == '$')
		{
			cmdLine.erase(0, cmdLine.find(' ') + 1);
			cmd = cmdLine.substr(0, cmdLine.find(' '));
			cmdLine.erase(0, cmdLine.find(' ') + 1);
			cmdArg = cmdLine.substr(0, cmdLine.size());

			if (cmd == "cd")
				execCd(&currentDir, cmdArg);
		}
		else if (cmdLine[0] == 'd')
		{
			partOne = cmdLine.substr(0, cmdLine.find(' '));
			partTwo = cmdLine.substr(cmdLine.find(' ') + 1, cmdLine.size());

			if (!isDirectoryAlreadyExists(currentDir, partTwo))
			{
				Directory* newDir = new Directory(partTwo, currentDir, dirId);
				dirId += 1;
				currentDir->addChildDir(newDir);
			}
		}
		else
		{
			partOne = cmdLine.substr(0, cmdLine.find(' '));
			partTwo = cmdLine.substr(cmdLine.find(' ') + 1, cmdLine.size());

			if (!isFilealreadyExists(currentDir, partTwo) && partOne != "")
			{
				File* newFile = new File(partTwo, std::stoi(partOne));
				currentDir->addFile(newFile);
				currentDir->setDirSize(currentDir->getDirSize() + std::stoi(partOne));
			}
		}
	}

	rootDir->updateDirSize(dirSizes);

	if (!isPartTwo)
		std::cout << rootDir->calcTotalDirSize() << std::endl;
	else
	{
		int spaceFree = 70000000 - rootDir->getDirSize();
		int spaceToFree = 30000000 - spaceFree;
		int dirSizeToDelete = 0;
		std::vector<int> sortedDirSizes = sortDirSizes(dirSizes);
		bool valueFound = false;

		for (int i = 0; i < sortedDirSizes.size(); i++)
		{
			if (sortedDirSizes[i] >= spaceToFree && !valueFound)
			{
				std::cout << sortedDirSizes[i] << std::endl;
				valueFound = true;
			}
		}
	}

}
