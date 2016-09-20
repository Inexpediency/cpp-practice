#include "stdafx.h"
#include "multyplex_matrix_utils.h"

using namespace std;

int main(int argc, char * argv[])
{
	matrix matrix1;
	matrix matrix2;
	if (!readMatrixFromInput(argc, argv, matrix1, matrix2))
	{
		return 1;
	}
	matrix result; 
	multyplyMatrix(result, matrix1, matrix2);
	printMatrix(result);
	return 0;
}

