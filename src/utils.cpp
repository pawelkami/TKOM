#include "utils.h"
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>

bool compareCaseInsensitive(const std::string& str1, const std::string& str2)
{
	if (str1.size() != str2.size())
		return false;

	return makeLowerCase(str1) == makeLowerCase(str2);
}

std::string makeLowerCase(const std::string & in)
{
	std::string out;

	std::transform(in.begin(), in.end(), std::back_inserter(out), tolower);
	return out;
}

