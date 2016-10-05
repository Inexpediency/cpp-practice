#include "stdafx.h"
#include "multmatrix_utils.h"

using namespace std;

int main(int argc, char * argv[])
{
	matrix matrix1;
	matrix matrix2;
	ifstream matrixFile1;
	ifstream matrixFile2;
	if (!CheckArgumentCount(argc) ||
		!OpenFile(matrixFile1, argv[1]) || !GetMatrix(matrixFile1, matrix1) || 
		!OpenFile(matrixFile2, argv[2]) || !GetMatrix(matrixFile2, matrix2))
	{
		return 1;
	}
	matrix result = MultyplyMatrix(matrix1, matrix2);
	PrintMatrix(result);
	return 0;
}

