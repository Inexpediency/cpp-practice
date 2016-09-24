#include "stdafx.h"
#include "crypt_utils.h"
#include <boost/utility/binary.hpp>

using namespace std;

bool CheckIsByteNumber(string str)
{
	int stringLen = str.length();
	int number = 0;
	for (int i = 0; i < stringLen; ++i)
	{
		char & currentChar = str[i];
		number = (number * 10 + (currentChar - '0'));
		if (('0' > currentChar) || (currentChar > '9') || (number > 255) || (number < 0))
		{
			return false;
		}
	}
	return true;
}

bool ProcesFileErrors(ifstream & input, ofstream & output, int namesCount, char * fileNames[])
{
	if (namesCount != 5)
	{
		cout << "Invalid argument count" << endl;
		return false;
	}
	if ((fileNames[1] != CRYPT_PREFIX) && (fileNames[1] != deCRYPT_PREFIX))
	{
		cout << "Invalid settings" << endl;
		return false;
	}
	if (!CheckIsByteNumber(fileNames[4]))
	{
		cout << "Invalid key" << endl;
		return false;
	}
	input.open(fileNames[2], ifstream::binary);
	if (!input.is_open())
	{
		cout << "Can not open input file" << endl;
		return false;
	}
	output.open(fileNames[3], ofstream::binary);
	if (!output.is_open())
	{
		cout << "Can not open output file" << endl;
		return false;
	}
	return true;
}

char MixByte(char byte)
{
	char temp = (byte << 2) & BOOST_BINARY(11100);
	temp |= (byte << 3) & BOOST_BINARY(11000000);
	temp |= (byte >> 5) & BOOST_BINARY(11);
	temp |= (byte >> 2) & BOOST_BINARY(100000);
	return temp;
}

char OrderByte(char byte)
{
	char temp = (byte >> 2) & BOOST_BINARY(111);
	temp |= (byte >> 3) & BOOST_BINARY(11000);
	temp |= (byte << 5) & BOOST_BINARY(1100000);																										
	temp |= (byte << 2) & BOOST_BINARY(10000000);
	return temp;
}

void Cript(ifstream & input, ofstream & output, char key)
{
	char currentByte;
	while (input.get(currentByte))
	{
		output.put(MixByte(currentByte ^ key));
	}
}

void Decript(ifstream & input, ofstream & output, char key)
{
	char currentByte;
	while (input.get(currentByte))
	{
		output.put(OrderByte(currentByte) ^ key);
	}
}