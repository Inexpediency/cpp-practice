#include "stdafx.h"
#include "find_text_utils.h"


using namespace std;

int main(int argc, char * argv[])
{
	ifstream inputFile;
	if (!ProcesFileErrors(argc, inputFile, argv))
	{
		return 0;
	}	
	if (FindStringInFile(inputFile, string(argv[2]), [](int lineIndex, const string &) {
		cout << lineIndex << endl;
	}))
	{
		cout << "String not found" << endl;
		return 1;
	}
	return 0;
}