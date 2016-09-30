#include "stdafx.h"
#include "../find_text/find_text_utils.h"

BOOST_AUTO_TEST_SUITE(OpenFileTests)
	
BOOST_AUTO_TEST_CASE(NotExistInputFile)
{
	std::ifstream inputFile;
	char * fileNames[] = { "", "not_exist_file.txt" };
	BOOST_CHECK(!ProcesFileErrors(3, inputFile, fileNames));
}

BOOST_AUTO_TEST_CASE(IncorrectArgumentsCount)
{
	std::ifstream inputFile;
	char * fileNames[] = { "", "" };
	BOOST_CHECK(!ProcesFileErrors(1, inputFile, fileNames));
}

BOOST_AUTO_TEST_CASE(EmptyFileTest)
{
	std::ifstream inputFile;
	char * fileNames[] = { "", "empty_test.txt" };
	BOOST_CHECK(ProcesFileErrors(3, inputFile, fileNames));
}

BOOST_AUTO_TEST_CASE(OnelineFileTest)
{
	std::ifstream inputFile;
	char * fileNames[] = { "", "oneline_test.txt" };
	BOOST_CHECK(ProcesFileErrors(3, inputFile, fileNames));
}

BOOST_AUTO_TEST_CASE(MultylineFileTest)
{
	std::ifstream inputFile;
	char * fileNames[] = { "", "multyline_test.txt" };
	BOOST_CHECK(ProcesFileErrors(3, inputFile, fileNames));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(PrintStrPosTests)

BOOST_AUTO_TEST_CASE(NoMatchedString)
{
	std::ifstream inputFile;
	char * fileNames[] = { "", "multyline_test.txt" };
	ProcesFileErrors(3, inputFile, fileNames);
	BOOST_CHECK(!FindStringInFile(inputFile, std::string("@@@")));
}

BOOST_AUTO_TEST_CASE(EmptyFileTest)
{
	std::ifstream inputFile;
	char * fileNames[] = { "", "empty_test.txt" };
	ProcesFileErrors(3, inputFile, fileNames);

	BOOST_CHECK(!FindStringInFile(inputFile, std::string("1")));
}

BOOST_AUTO_TEST_CASE(OnelineFileTest)
{
	std::ifstream inputFile;
	char * fileNames[] = { "", "oneline_test.txt" };
	ProcesFileErrors(3, inputFile, fileNames);
	BOOST_CHECK(FindStringInFile(inputFile, std::string("12")));
}

BOOST_AUTO_TEST_CASE(MultylineFileTest)
{
	std::ifstream inputFile;
	char * fileNames[] = { "", "multyline_test.txt" };
	ProcesFileErrors(3, inputFile, fileNames);
	BOOST_CHECK(FindStringInFile(inputFile, std::string("12")));
}

BOOST_AUTO_TEST_SUITE_END()