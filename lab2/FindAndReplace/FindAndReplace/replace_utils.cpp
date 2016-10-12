#include "stdafx.h"
#include "replace_utils.h"

bool CheckArgumentCount(int argumentCount)
{
	if (argumentCount != 3)
	{
		std::cout << "Invalid argument count" << std::endl;
	}
	return argumentCount == 3;
}

bool CheckReplacingString(const std::string & str)
{
	if (str == "")
	{
		std::cout << "Replacing string can not be empty" << std::endl;
	}
	return str != "";
}

std::string FindAndReplace(const std::string & subject, const std::string & search, const std::string & replace)
{
	std::string result = "";
	auto pos = subject.find(search, 0);
	auto startPos = 0;
	while (pos != subject.size())
	{
		result += subject.substr(startPos, pos);
		pos = subject.find(search, startPos);
		startPos = pos;
	}
	result += subject.substr(startPos, pos);
	return result;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    