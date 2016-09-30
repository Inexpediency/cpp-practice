#pragma once

const int MATRIX_SIZE = 3;
typedef int matrix[MATRIX_SIZE][MATRIX_SIZE];

bool ReadMatrixFromInput(int fileCount, char * fileNames[], matrix & matrix1, matrix & matrix2);
void PrintMatrix(matrix const  & outMatrix);
void MultyplyMatrix(matrix & result, matrix & matrix1, matrix & matrix2);
bool CompareMatrix(matrix const & matrix1, matrix const & matrix2);