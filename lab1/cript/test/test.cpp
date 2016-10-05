#include "stdafx.h"
#include "../crypt/cript_utils.h"

using namespace std;

bool isFileEque(ifstream & file1, ifstream & file2)
{
	char firstFilechar, secondFilechar;
	while (file1.get(firstFilechar) && file2.get(secondFilechar))
	{
		if (firstFilechar != secondFilechar)
		{
			return false;
		}
	}
	return true;
}

BOOST_AUTO_TEST_SUITE(InputDataProcess)

BOOST_AUTO_TEST_CASE(CheckKeyTest)
{
	BOOST_CHECK(CheckKey("123"));
	BOOST_CHECK(!CheckKey("ô123"));
	BOOST_CHECK(!CheckKey("1ô23"));
	BOOST_CHECK(!CheckKey("123ô"));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CryptDecrypt)

BOOST_AUTO_TEST_CASE(CryptDecrypt)
{
	ifstream input("text.txt");
	ofstream output("output.txt");

	uint8_t key = stoi("123", nullptr, 10);
	Encode(input, output, key, Cript);
	output.close();
	ifstream cryptedInput("outout.txt");
	ofstream newInput("decrypted_output.txt");
	Encode(cryptedInput, newInput, key, Decript);
	newInput.close();
	cryptedInput.clear();
	cryptedInput.seekg(0);
	ifstream newInputDecript("decrypted_output.txt");
	BOOST_CHECK(isFileEque(input, newInputDecript));
}

BOOST_AUTO_TEST_SUITE_END()