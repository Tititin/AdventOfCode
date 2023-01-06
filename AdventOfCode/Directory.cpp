#include "Directory.h"

Directory::Directory(const std::string& name, Directory* parentDir, const int& id)
{
	_id = id;
	_name = name;
	_parentDirectory = parentDir;
	_dirSize = 0;
}

Directory::~Directory()
{
	_childDirectories.clear();
	_files.clear();
}

const std::string& Directory::getName()
{
	return (_name);
}

const int& Directory::getDirSize()
{
	return (_dirSize);
}

Directory* Directory::getParentDirectory()
{
	if (_parentDirectory != nullptr)
		return (_parentDirectory);
	else
		return (nullptr);
}

std::list<Directory*>& Directory::getChildDirectories()
{
	return (_childDirectories);
}

std::list<File*>& Directory::getFiles()
{
	return (_files);
}

void Directory::setName(const std::string& name)
{
	_name = name;
}

void Directory::setDirSize(const int& size)
{
	_dirSize = size;
}

void Directory::addFile(File* file)
{
	_files.push_back(file);
}

void Directory::addChildDir(Directory* dir)
{
	_childDirectories.push_back(dir);
}

int Directory::updateDirSize(std::map<int, int>& dirSizes)
{
	int size = 0;

	for (Directory* dir : _childDirectories)
		size += dir->updateDirSize(dirSizes);
	for (File* file : _files)
		size += file->getSize();

	_dirSize = size;

	if (dirSizes.find(_id) == dirSizes.end() || dirSizes.empty())
		dirSizes.insert(std::pair<int, int>(_id, _dirSize));
	else if (dirSizes.find(_id) != dirSizes.end())
		dirSizes[_id] = _dirSize;


	return (_dirSize);
}

int Directory::calcTotalDirSize()
{
	int size = 0;
	if (_dirSize <= 100000)
		size += _dirSize;
	for (Directory* dir : _childDirectories)
		size += dir->calcTotalDirSize();
	return (size);
}
