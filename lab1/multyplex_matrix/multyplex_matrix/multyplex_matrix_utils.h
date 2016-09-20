#pragma once

const int matrixSize = 3;
typedef int matrix[matrixSize][matrixSize];

bool readMatrixFromInput(int fileCount, char * fileNames[], matrix & matrix1, matrix & matrix2);
void printMatrix(matrix const  & outMatrix);
void multyplyMatrix(matrix & result, matrix & matrix1, matrix & matrix2);
bool compareMatrix(matrix const & matrix1, matrix const & matrix2);