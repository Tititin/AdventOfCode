#pragma once

#include <list>
#include <string>

class File
{
public:
	File(const std::string& name, const int& size);
	~File();

private:
	std::string _name;
	int			_size;

public:
	const std::string& getName();
	const int& getSize();

	void setName(const std::string& name);
	void setSize(const int& size);
};

