#include "stdafx.h"
#include "find_text_utils.h"


using namespace std;

int main(int argc, char * argv[])
{
	
	ifstream inputFile;
	if (!procesFileErrors(argc, inputFile, argv))
	{
		return 0;
	}	
	return printStringPos(inputFile, argv[2]);
}

