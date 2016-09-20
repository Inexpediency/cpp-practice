#include "stdafx.h"
#include "multyplex_matrix_utils.h"

using namespace std;

bool getMatrixLine(string inputString, int gettingMatrixLine[matrixSize])
{
	int stringLen = inputString.length();
	int currentElIndex = 0;
	bool isElementInitialize = false;
	gettingMatrixLine[currentElIndex] = 0;
	for (int i = 0; i < stringLen; ++i)
	{
		char & currentSymbol = inputString[i];
		if (currentSymbol > '9' || currentSymbol < '0')
		{
			++currentElIndex;
			gettingMatrixLine[currentElIndex] = 0;
			isElementInitialize = false;
		}
		else
		{
			isElementInitialize = true;
			gettingMatrixLine[currentElIndex] += 10 * gettingMatrixLine[currentElIndex] + (currentSymbol - '0');
		}
	}
	return (currentElIndex == matrixSize - 1) && isElementInitialize;
}

bool getMatrix(ifstream & inputFile, matrix & gettingMatrix)
{
	string line;
	int i;
	for (i = 0; getline(inputFile, line); ++i)
	{
		if (i >= matrixSize || !getMatrixLine(line, gettingMatrix[i]))
		{
			return false;
		}
	}
	return i == matrixSize;
}

bool readMatrixFromInput(int fileCount, char * fileNames[], matrix & matrix1, matrix & matrix2)
{
	if (fileCount != 3)
	{
		cout << "Invalid argument count" << endl;
		return false;
	}
	ifstream matrixFile1(fileNames[1]);
	ifstream matrixFile2(fileNames[2]);
	if (!getMatrix(matrixFile1, matrix1))
	{
		cout << "Invalid first file";
		return false;
	}
	if (!getMatrix(matrixFile2, matrix2))
	{
		cout << "Invalid second file";
		return false;
	}
	return true;
}

bool compareMatrix(matrix const & matrix1, matrix const & matrix2)
{
	for (int i = 0; i < matrixSize; ++i)
	{
		for (int j = 0; j < matrixSize; ++j)
		{
			if (matrix1[i][j] != matrix2[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

void printMatrix(matrix const & outMatrix)
{
	for (int i = 0; i < matrixSize; ++i)
	{
		for (int j = 0; j < matrixSize; ++j)
		{
			cout << outMatrix[i][j] << " ";
		}
		cout << endl;
	}
}

void multyplyMatrix(matrix & result, matrix & matrix1, matrix & matrix2)
{
	for (int i = 0; i < matrixSize; ++i)
	{
		for (int j = 0; j < matrixSize; ++j)
		{
			result[i][j] = 0;
			for (int k = 0; k < matrixSize; ++k)
			{
				result[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}
}