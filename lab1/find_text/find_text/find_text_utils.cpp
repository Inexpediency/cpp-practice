#include "stdafx.h"
#include "find_text_utils.h"

//using namespace std;


bool ProcesFileErrors(int namesCount, std::ifstream & input, char * fileNames[])
{
	if (namesCount != 3)
	{
		std::cout << "Invalid argument count" << std::endl;
		return false;
	}
	input.open(fileNames[1]);
	if (!input.is_open())
	{
		std::cout << "Can not open input file" << std::endl;
		return false;
	}
	return true;
}

bool FindStringInFile(std::ifstream & input, const std::string & comparedString, const findStringCallback & callback)
{
	std::string tempString;
	bool isFound = false;
	for (int currentLine = 1; std::getline(input, tempString); ++currentLine)
	{
		if (tempString.find(comparedString, 0) != std::string::npos)
		{
			isFound = true;
			callback(currentLine, tempString);
		}
	}
	return isFound;
}

bool FindStringInFile(std::ifstream & input, const std::string & comparedString)
{
	std::string tempString;
	bool isFound = false;
	for (int currentLine = 1; std::getline(input, tempString); ++currentLine)
	{
		if (tempString.find(comparedString, 0) != std::string::npos)
		{
			isFound = true;
		}
	}
	return isFound;
}