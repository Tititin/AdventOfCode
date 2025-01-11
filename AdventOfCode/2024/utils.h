#pragma once

#include <functional>
#include <queue>

#include "FileParser.h"

class FunctionQueue
{
private:
	std::queue<std::function<void()>>	tasks;
public:
	size_t	getSize();

	void	addTask(std::function<void()> _task);

	void	executeTasks();
};

std::string& operator*(std::string& _left, const unsigned long long int& _right);

bool& operator==(const t_Pos& _left, const t_Pos& _right);
bool& operator!=(const t_Pos& _left, const t_Pos& _right);
