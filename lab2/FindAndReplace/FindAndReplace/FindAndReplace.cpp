#include "stdafx.h"
#include "replace_utils.h"

int main(int argc, char * argv[])
{
	if (!CheckArgumentCount(argc) || !CheckReplacingString(argv[1]))
	{
		return 1;
	}
	std::string line;
	while (std::getline(std::cin, line))
	{
		std::cout << FindAndReplace(line, argv[1], argv[2]);
	}
	return 0;
}

