#include "Elf.h"

Elf::Elf()
{
	_calories = 0;
}

Elf::Elf(const int& calories)
{
	_calories = calories;
}

Elf::~Elf()
{

}

void Elf::setCalories(const int& calories)
{
	_calories = calories;
}

const int& Elf::getCalories() const
{
	return (_calories);
}

void Elf::addCalories(const int& calories)
{
	_calories += calories;
}

bool Elf::subCalories(const int& calories)
{
	if (_calories - calories >= 0)
	{
		_calories -= calories;
		return (true);
	}
	else
		return (false);
}