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

std::string trimWhitespaces(const std::string& str)
{
    if(str.empty())
        return "";

	std::string res;
	std::locale loc;
	unsigned long beginIndex = 0;
    for(; beginIndex < str.size(); ++beginIndex)
	{
		if(!isspace(str[beginIndex], loc))
            break;
	}

    unsigned long endIndex = str.size()-1;
    for(; endIndex > beginIndex; --endIndex)
    {
        if(!isspace(str[endIndex],loc))
            break;
    }

    return str.substr(beginIndex, endIndex-beginIndex+1);
}

std::string replaceSpaces(const std::string& str) {
    std::string temp = str;
    std::transform(temp.begin(), temp.end(), temp.begin(), [](char ch) {
        return ch == ' ' ? '_' : ch;
    });

    return temp;
}


