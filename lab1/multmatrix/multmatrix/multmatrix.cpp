#include "stdafx.h"
#include "multmatrix_utils.h"

using namespace std;

int main(int argc, char * argv[])
{
	matrix matrix1;
	matrix matrix2;
	if (argc != 3)
	{
		cout << "Invalid argument count" << endl;
		return 1;
	}
	ifstream matrixFile1(argv[1]);
	if (!(matrixFile1.is_open() && GetMatrix(matrixFile1, matrix1)))
	{
		cout << "Invalid first file";
		return 1;
	}
	ifstream matrixFile2(argv[2]);
	if (!(matrixFile2.is_open() && GetMatrix(matrixFile2, matrix2)))
	{
		cout << "Invalid second file";
		return 1;
	}
	matrix result = MultyplyMatrix(matrix1, matrix2);
	PrintMatrix(result);
	return 0;
}

