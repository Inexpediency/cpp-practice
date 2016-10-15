#include "stdafx.h"
#include "prime_nubers_utils.h"

bool CheckArgumentCount(int arumentCount)
{
	if (arumentCount != 2)
	{
		std::cout << "Incorrect argument count" << std::endl;
	}
	return arumentCount == 2;
}

bool CheckUpperBound(std::string upperBound)
{
	for (size_t i = 0; i < upperBound.size(); ++i)
	{
		if (upperBound[i] < '0' || upperBound[i] > '9')
		{
			std::cout << "Invalid upper bound" << std::endl;
			return false;
		}
	}
	unsigned long upperBoundNumber = std::stoul(upperBound);
	bool isKeyCorrect = upperBoundNumber >= 2;
	if (!isKeyCorrect)
	{
		std::cout << "Invalid upper bound" << std::endl;
	}
	return isKeyCorrect;
}

void InitPrimeNumbersVector(std::vector<bool> & primeNumbers, int upperBound)
{
	for (size_t i = 0; i <= upperBound; ++i)
	{
		primeNumbers.push_back((i % 2 != 0));
	}
	primeNumbers[0] = false;
	primeNumbers[1] = false;
	primeNumbers[2] = true;
}

void DelNotPrimeNumbers(std::vector<bool> & primeNumbers)
{
	size_t primeNumbersVectorSize = primeNumbers.size();
	size_t endIndex = floor(sqrt(primeNumbersVectorSize));
	for (size_t i = 3; i <= endIndex; ++i)
	{
		if (primeNumbers[i])
		{
			for (size_t j = i * i; j < primeNumbersVectorSize; j = j + i)
			{
				primeNumbers[j] = false;
			}
		}
	}
}

void TransformPrimeNumbersVectorToSet(const std::vector<bool> & primeNumbersVector, std::set<int> & primeNumbersSet)
{
	for (size_t i = 0; i < primeNumbersVector.size(); ++i)
	{
		if (primeNumbersVector[i])
		{
			primeNumbersSet.insert(i);
		}
	}
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::vector<bool> primeNumbers;
	primeNumbers.reserve(upperBound + 1);
	InitPrimeNumbersVector(primeNumbers, upperBound);
	DelNotPrimeNumbers(primeNumbers);
	std::set<int> primeNumbersSet;
	TransformPrimeNumbersVectorToSet(primeNumbers, primeNumbersSet);
	return primeNumbersSet;
}