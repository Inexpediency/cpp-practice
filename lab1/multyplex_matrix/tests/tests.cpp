#include "stdafx.h"
#include "../multyplex_matrix/multyplex_matrix_utils.h"

BOOST_AUTO_TEST_SUITE(CheckInputData)

BOOST_AUTO_TEST_CASE(IncorrectArgumentCount)
{
	char * fileNames[] = { "", "correctMatrix.txt", "correctMatrix.txt" };
	matrix a, b;
	BOOST_CHECK(!readMatrixFromInput(2, fileNames, a, b));
}

BOOST_AUTO_TEST_CASE(IncorrectInputFile)
{
	char * fileNames[] = { "", "incorrectMatrix.txt", "correctMatrix.txt" };
	matrix a, b;
	BOOST_CHECK(!readMatrixFromInput(3, fileNames, a, b));
}

BOOST_AUTO_TEST_CASE(CorrectArgument)
{
	char * fileNames[] = { "", "correctMatrix.txt", "correctMatrix.txt" };
	matrix a, b;
	BOOST_CHECK(!readMatrixFromInput(3, fileNames, a, b));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CheckMyltyply)

BOOST_AUTO_TEST_CASE(Check)
{
	matrix a = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};
	matrix b = {
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 9 }
	};
	matrix result;
	multyplyMatrix(result, a, b);
	BOOST_CHECK(compareMatrix(result, {
		{30, 36, 42},
		{66, 81, 96},
		{102, 126, 150}
	}));
}

BOOST_AUTO_TEST_SUITE_END()
