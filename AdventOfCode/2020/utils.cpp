#include "utils.h"

std::string readWord(std::istringstream& _stream)
{
	std::string word;

	_stream >> word;

	return (word);
}

std::string& operator*(std::string& _left, const unsigned long long int& _right)
{
	std::string result;
	unsigned long long int  ret = 0;

	for (int i = _left.size() - 1; i >= 0; i--)
	{
		int unit = _left[i] - '0';

		unit *= _right;
		result.insert(result.begin(), (unit % 10) + '0');
		ret = unit / 10;
	}
	if (ret != 0)
		result.insert(result.begin(), ret + '0');

	return (result);
}

bool& operator==(const t_Pos& _left, const t_Pos& _right)
{
	bool    result = _left.x == _right.x && _left.y == _right.y;

	return (result);
}

bool& operator!=(const t_Pos& _left, const t_Pos& _right)
{
	bool    result = _left.x != _right.x || _left.y != _right.y;

	return (result);
}

size_t FunctionQueue::getSize()
{
	return size_t(tasks.size());
}

void FunctionQueue::addTask(std::function<void()> _task)
{
	tasks.push(_task);
}

void FunctionQueue::executeTasks()
{
	while (!tasks.empty())
	{
		auto task = tasks.front();
		tasks.pop();

		task();
	}
}