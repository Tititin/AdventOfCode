#include "File.h"

File::File(const std::string& name, const int& size)
{
	_name = name;
	_size = size;
}

File::~File()
{

}

const std::string& File::getName()
{
	return (_name);
}

const int& File::getSize()
{
	return (_size);
}

void File::setName(const std::string& name)
{
	_name = name;
}

void File::setSize(const int& size)
{
	_size = size;
}

