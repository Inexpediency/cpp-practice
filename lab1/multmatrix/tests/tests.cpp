#include "stdafx.h"
#include "../multmatrix/multmatrix_utils.h"

bool CompareMatrix(matrix const & matrix1, matrix const & matrix2)
{
	for (int i = 0; i < MATRIX_SIZE; ++i)
	{
		for (int j = 0; j < MATRIX_SIZE; ++j)
		{
			if (matrix1[i][j] != matrix2[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

BOOST_AUTO_TEST_SUITE(GetMatrixTest)

BOOST_AUTO_TEST_CASE(CorrectInputFile)
{
	std::ifstream input("correct_matrix.txt");
	matrix a;
	BOOST_CHECK(GetMatrix(input, a));
	matrix correctMatrix;
	correctMatrix[0] = { 1, 2, 3 };
	correctMatrix[1] = { 4, 5, 6 };
	correctMatrix[2] = { 7, 8, 9 };
	BOOST_CHECK(CompareMatrix(correctMatrix, a));
}

BOOST_AUTO_TEST_CASE(IncorrectInputFile)
{
	std::ifstream input("incorrectMatrix.txt");
	matrix a;
	BOOST_CHECK(!GetMatrix(input, a));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CheckMyltyply)

BOOST_AUTO_TEST_CASE(Check)
{
	matrix a;
	a[0] = { 1, 2, 3 };
	a[1] = { 4, 5, 6 };
	a[2] = { 7, 8, 9 };
	matrix b;
	b[0] = { 1, 2, 3 };
	b[1] = { 4, 5, 6 };
	b[2] = { 7, 8, 9 };
	matrix result = MultyplyMatrix(a, b);
	matrix correctResult;
	correctResult[0] = {  30,  36,  42 };
	correctResult[1] = {  66,  81,  96 };
	correctResult[2] = { 102, 126, 150 };
	BOOST_CHECK(CompareMatrix(result, correctResult));
}

BOOST_AUTO_TEST_SUITE_END()
