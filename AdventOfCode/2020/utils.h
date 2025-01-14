#pragma once

#include <functional>
#include <queue>
#include <type_traits>

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

std::string readWord(std::istringstream& _stream);

std::string& operator*(std::string& _left, const unsigned long long int& _right);

bool& operator==(const t_Pos& _left, const t_Pos& _right);
bool& operator!=(const t_Pos& _left, const t_Pos& _right);

template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, void>::type
sortVector(std::vector<T>& _array)
{
	bool isSorted = false;

	while (!isSorted)
	{
		isSorted = true;

		for (int i = 0; i < _array.size() - 1 && isSorted; i++)
			if (_array[i] > _array[i + 1])
			{
				isSorted = false;

				T tmp = _array[i];
				_array[i] = _array[i + 1];
				_array[i + 1] = tmp;
			}
	}
}
