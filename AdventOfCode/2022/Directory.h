#pragma once

#include "File.h"
#include <list>
#include <map>
#include <iostream>

class Directory
{
public:
	Directory(const std::string& name, Directory* parentDir = NULL, const int& id = 0);
	~Directory();

private:
	int						_id;

	std::string				_name;
	int						_dirSize;

	Directory*				_parentDirectory;
	std::list<Directory*>	_childDirectories;
	std::list<File*>		_files;

public:
	const std::string& getName();
	const int& getDirSize();

	Directory* getParentDirectory();
	std::list<Directory*>& getChildDirectories();
	std::list<File*>& getFiles();

	void setName(const std::string& name);
	void setDirSize(const int& size);

	void addFile(File* file);
	void addChildDir(Directory* dir);

	int updateDirSize(std::map<int, int> &dirSizes);
	int calcTotalDirSize();
};

