#include "stdafx.h"
#include "flip_byte_utils.h"

using namespace std;

bool chelIsByteNumber(string str)
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

bool checkInput(int inputCount, char * inputValue[])
{
	if (inputCount != 2)
	{
		cout << "Invalid argument count" << endl;
		return false;
	}
	char inputNumber = 0;
	if (!chelIsByteNumber(inputValue[1]))
	{
		cout << "This is not a byte number" << endl;
		return false;
	}
	return true;
}

unsigned char flipByte(char number)
{
	char mask1 = 0;
	char mask2 = 0;
	for (int i = 0; i < 4; ++i)
	{
		mask1 = ((number >> (7 - i)) & 0x01) << i;
		mask2 = ((number >> i) & 0x01) << (7 - i);
		number &= ~(0x01 << (7 - i));
		number &= ~(0x01 << i);
		number |= mask2;
		number |= mask1;
	}
	return number;
}			