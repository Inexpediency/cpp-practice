#include "stdafx.h"
#include "cript_utils.h"

using namespace std;

int main(int argc, char * argv[])
{
	ifstream input;
	ofstream output;
	if (CheckArgumentCount(argc) && 
		CheckSettings(argv[1]) && CheckKey(argv[4]) &&
		OpenFile(input, argv[2]) && OpenFile(output, argv[3]))
	{
		return 1;
	}
	char key = stoi(argv[4], nullptr, 10);
	if (argv[1] == DECRIPT_PREFIX)
	{
		Encode(input, output, key, Decript);
	}
	else
	{
		Encode(input, output, key, Cript);
	}
    return 0;
}

