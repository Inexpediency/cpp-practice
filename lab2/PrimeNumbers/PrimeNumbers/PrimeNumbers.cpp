#include "stdafx.h"
#include "prime_nubers_utils.h"

int main(int argc, char * argv[])
{
	if (!CheckArgumentCount(argc) || !CheckUpperBound(argv[1]))
	{
		return 1;
	}
	unsigned long upperBound = std::stoul(argv[1]);
	std::set<int> primeNumbers = GeneratePrimeNumbersSet(upperBound);
	for (auto element : primeNumbers)
	{
		std::cout << element << std::endl;
	}
	std::cout << primeNumbers.size() << std::endl;
    return 0;
}