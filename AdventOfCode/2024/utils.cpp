#include "utils.h"

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
