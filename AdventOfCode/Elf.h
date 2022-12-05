#pragma once
class Elf
{
public:
	Elf();
	Elf(const int& calories);
	~Elf();
private:
	int _calories;

public:
	void setCalories(const int& calories);
	const int& getCalories() const;

	void addCalories(const int& calories);
	bool subCalories(const int& calories);
};

