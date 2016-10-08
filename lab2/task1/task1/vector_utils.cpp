#include "stdafx.h"
#include "vector_utils.h"

doubleVector ReadVector(std::istream & input)
{
	double tempNumber;
	doubleVector tempVector;	
	while (input >> tempNumber)
	{
		tempVector.push_back(tempNumber);
	}
	return tempVector;
}

double GetPositiveElementSumm(const doubleVector & processingVector)
{
	double positiveElementSum = 0;
	for (auto element : processingVector)
	{
		if (element > 0)
		{
			positiveElementSum += element;
		}
	}
	return positiveElementSum;
}

void ProcessVector(doubleVector & processingVector)
{
	double positiveElementSum = GetPositiveElementSumm(processingVector);
	bool isEven = true;
	for (auto & element : processingVector)
	{
		if (isEven)
		{
			element = element * 2;
		}
		else
		{
			element -= positiveElementSum;
		}
	}
}

void PrintSortedVector(std::ostream & output, doubleVector & printingVector)
{
	std::sort(printingVector.begin(), printingVector.end(), [](double i, double j) {
		return i < j;
	});
	for (const auto doubleNumb : printingVector)
	{
		output << doubleNumb << " ";
	}
	output << std::endl;
}