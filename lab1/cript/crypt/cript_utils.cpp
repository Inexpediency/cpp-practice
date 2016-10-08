#include "stdafx.h"
#include "cript_utils.h"

using namespace std;

bool CheckArgumentCount(int argumentCount)
{
	if (argumentCount != 5)
	{
		cout << "Invalid argument count" << endl;
	}
	return argumentCount == 5;
}

bool CheckSettings(const string & setting)
{
	bool isSettingsCorrect = (setting != CRIPT_PREFIX) && (setting != DECRIPT_PREFIX);
	if (!isSettingsCorrect)
	{
		cout << "Invalid settings" << endl;
	}
	return isSettingsCorrect;
}

bool CheckKey(const string & key)
{
	for (size_t i = 0; i < key.size(); ++i)
		if (key[i] < '0' || key[i] > '9')
		{
			cout << "Invalid key" << endl;
			return false;
		}
	unsigned long keyNumber = stoul(key);
	bool isKeyCorrect =	keyNumber < 256;
	if (!isKeyCorrect)
	{
		cout << "Invalid key" << endl;
	}
	return isKeyCorrect;
}

bool OpenFile(ifstream & file, string fileName)
{
	file.open(fileName, ifstream::binary);
	if (!file.is_open())
	{
		cout << "Can not open " << fileName << " file" << endl;
	}
	return file.is_open();
}

bool OpenFile(ofstream & file, string fileName)
{
	file.open(fileName, ifstream::binary);
	if (!file.is_open())
	{
		cout << "Can not open " << fileName << " file" << endl;
	}
	return file.is_open();
}

uint8_t Cript(uint8_t byte, uint8_t key)
{
	uint8_t temp = (byte << 2) & 0b11100;
	temp |= (byte << 3) & 0b11000000;
	temp |= (byte >> 5) & 0b11;
	temp |= (byte >> 2) & 0b100000;
	return temp ^ key;
}

uint8_t Decript(uint8_t byte, uint8_t key)
{
	char temp = (byte >> 2) & 0b111;
	temp |= (byte >> 3) & 0b11000;
	temp |= (byte << 5) & 0b1100000;
	temp |= (byte << 2) & 0b10000000;
	return temp ^ key;
}

void Encode(ifstream & input, ofstream & output, uint8_t key, const function<uint8_t(uint8_t byte, uint8_t key)> & EncodingFunction)
{
	char currentByte;
	while (input.get(currentByte))
	{
		output.put(EncodingFunction(currentByte, key));
	}
}