#pragma once
#include <string>
#include <utility>

namespace Utils
{
	static std::string coordToString(const std::pair<int, int>& coord)
	{
		return { char(coord.second + 'a'), char(8 - coord.first + '0') };
	}

	static std::pair<int, int> stringToCoord(const std::string& str)
	{
		return { 8 - str[1] + '0', str[0] - 'a' };
	}
}