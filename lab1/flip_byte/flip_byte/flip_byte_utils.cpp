#include "stdafx.h"
#include "flip_byte_utils.h"

using namespace std;

bool CheckIsByteNumber(const string str)
{
	size_t stringLen = str.length();
	int number = 0;
	for (size_t i = 0; i < stringLen; ++i)
	{
		number = (number * 10 + (str[i] - '0'));
		if (('0' > str[i]) || (str[i] > '9') || (number > 255) || (number < 0))
    	{
			return false;
		}
	}
	return true;
}

bool CheckInput(int inputCount, char * inputValue[])
{
	if (inputCount != 2)
	{
		cout << "Invalid argument count" << endl;
		return false;
	}
	if (!CheckIsByteNumber(inputValue[1]))
	{
		cout << "This is not a byte number" << endl;
		return false;
	}
	return true;
}

uint8_t FlipByte(uint8_t number)
{
	uint8_t temp = (number << 4) & 0b11110000;
	number = (number >> 4) & 0b00001111;
	number |= temp;
	temp = (number >> 2) & 0b00110011;
	number = (number << 2) & 0b11001100;
	number |= temp;
	temp = (number >> 1) & 0b01010101;
	number = (number << 1) & 0b10101010;
	number |= temp;
	return number;
}			