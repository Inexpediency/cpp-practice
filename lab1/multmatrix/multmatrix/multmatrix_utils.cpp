#include "stdafx.h"
#include "multmatrix_utils.h"

using namespace std;

bool CheckArgumentCount(int argumentCount)
{
	if (argumentCount != 3)
	{
		cout << "Invalid argumentCount" << endl;
	}
	return argumentCount != 3;
}

bool OpenFile(ifstream & fileStream, char * fileName)
{
	fileStream.open(fileName);
	if (fileStream.is_open())
	{
		cout << "Can not open " << fileName << endl;
	}
	return fileStream.is_open();
}

bool GetMatrixLine(string inputString, array<float, MATRIX_SIZE> & gettingMatrixLine)
{
	stringstream strStream(inputString);
	for (size_t i = 0; i < MATRIX_SIZE; ++i)
	{
		if (!strStream.good())
		{
			return false;
		}
		strStream >> gettingMatrixLine[i];
	}
	return true;
}

bool GetMatrix(ifstream & inputFile, matrix & gettingMatrix)
{
	string line;
	int i;
	for (i = 0; getline(inputFile, line); ++i)
	{
		if (i >= MATRIX_SIZE || !GetMatrixLine(line, gettingMatrix[i]))
		{
			cout << "Invalid matrix";
			return false;
		}
	}
	return i == MATRIX_SIZE;
}

void PrintMatrix(const matrix & outMatrix)
{
	for (int i = 0; i < MATRIX_SIZE; ++i)
	{
		for (int j = 0; j < MATRIX_SIZE; ++j)
		{
			cout << outMatrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

matrix MultyplyMatrix(const matrix & matrix1, const matrix & matrix2)
{
	matrix result;
	for (int i = 0; i < MATRIX_SIZE; ++i)
	{
		for (int j = 0; j < MATRIX_SIZE; ++j)
		{
			result[i][j] = 0;
			for (int k = 0; k < MATRIX_SIZE; ++k)
			{
				result[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}
	return result;
}