#include "stdafx.h"
#include "../crypt/crypt_utils.h"

using namespace std;

bool CompareFile(ifstream & file1, ifstream & file2)
{
	char firstFileChar, secondFileChar;
	while (file1.get(firstFileChar) && file2.get(secondFileChar))
	{
		if (firstFileChar != secondFileChar)
		{
			return false;
		}
	}
	return true;
}

BOOST_AUTO_TEST_SUITE(InputDataProcess)

BOOST_AUTO_TEST_CASE(IncorrectArgumentsCount)
{
	std::ifstream input;
	std::ofstream output;
	char * fileNames[] = { "",  const_cast<char *>(CRYPT_PREFIX.c_str()), "text.txt", "output.txt", "123" };
	BOOST_CHECK(!ProcesFileErrors(input, output, 1, fileNames));
	BOOST_CHECK(!ProcesFileErrors(input, output, 6, fileNames));
}

BOOST_AUTO_TEST_CASE(IncorrectInputFileName)
{
	std::ifstream input;
	std::ofstream output;
	char * fileNames[] = { "",  const_cast<char *>(CRYPT_PREFIX.c_str()), "not_exist_file.txt", "output.txt", "123" };
	BOOST_CHECK(!ProcesFileErrors(input, output, 5, fileNames));
}

BOOST_AUTO_TEST_CASE(IncorrectSettings)
{
	std::ifstream input;
	std::ofstream output;
	char * fileNames[] = { "",  "not_exist_settings", "text.txt", "output.txt", "123" };
	BOOST_CHECK(!ProcesFileErrors(input, output, 5, fileNames));
}


BOOST_AUTO_TEST_CASE(IncorrectKey)
{
	std::ifstream input;
	std::ofstream output;
	char * fileNames[] = { "",  const_cast<char *>(CRYPT_PREFIX.c_str()), "text.txt", "output.txt", "1234" };
	BOOST_CHECK(!ProcesFileErrors(input, output, 5, fileNames));
}

BOOST_AUTO_TEST_CASE(CorrectWork)
{
	std::ifstream input;
	std::ofstream output;
	char * fileNames[] = { "",  const_cast<char *>(CRYPT_PREFIX.c_str()), "text.txt", "output.txt", "123" };
	BOOST_CHECK(ProcesFileErrors(input, output, 5, fileNames));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CryptDecrypt)

BOOST_AUTO_TEST_CASE(CryptDecrypt)
{
	ifstream input;
	ofstream output;
	char * fileNames[] = { "",  const_cast<char *>(CRYPT_PREFIX.c_str()), "text.txt", "output.txt", "12" };
	ProcesFileErrors(input, output, 5, fileNames);
	
	char key = stoi(fileNames[4], nullptr, 10);
	Cript(input, output, key);
	output.close();
	ifstream cryptedInput(fileNames[3]);
	ofstream newInput("decrypted_output.txt");
	Decript(cryptedInput, newInput, key);
	newInput.close();
	cryptedInput.clear();
	cryptedInput.seekg(0);
	ifstream newInputDecript("decrypted_output.txt");
	BOOST_CHECK(CompareFile(input, newInputDecript));
}

BOOST_AUTO_TEST_SUITE_END()