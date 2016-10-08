#include "stdafx.h"
#include "vector_utils.h"

int main()
{
	doubleVector processingVector = ReadVector(std::cin);
	ProcessVector(processingVector);
	PrintSortedVector(std::cout, processingVector);
	return 0;
}

