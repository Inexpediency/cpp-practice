#include "stdafx.h"
#include "crypt_utils.h"

using namespace std;

int main(int argc, char * argv[])
{
	ifstream input;
	ofstream output;
	if (!ProcesFileErrors(input, output, argc, argv))
	{
		return 1;
	}
	char key = stoi(argv[4], nullptr, 10);
	if (argv[1] == CRYPT_PREFIX)
	{
		Cript(input, output, key);
	}
	else
	{
	    Decript(input, output, key);
	}
    return 0;
}

