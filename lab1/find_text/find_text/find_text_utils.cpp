#include "stdafx.h"
#include "find_text_utils.h"

using namespace std;

bool procesFileErrors(int namesCount, std::ifstream & input, char * fileNames[])
{
	if (namesCount != 3)
	{
		cout << "Invalid argument count" << endl;
		return false;
	}
	input.open(fileNames[1]);
	if (!input.is_open())
	{
		cout << "Can not open input file" << endl;
		return false;
	}
	return true;
}

int printStringPos(ifstream & input, string comparedString)
{
	string tempString;
	bool findStatus = 1;
	for (int currentLine = 1; getline(input, tempString); ++currentLine)
	{
		if (tempString.find(comparedString, 0) != string::npos)
		{
			findStatus = 0;
			cout << currentLine << endl;
		}
	}
	if (findStatus == 1)
	{
		cout << comparedString << " not found" << endl;
	}
	return findStatus;
}