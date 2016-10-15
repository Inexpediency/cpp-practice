#include "stdafx.h"
#include "../PrimeNumbers/prime_nubers_utils.h"

BOOST_AUTO_TEST_SUITE(Test_GeneratePrimeNumbers)
	BOOST_AUTO_TEST_SUITE(Find_all_prime_numbers_test)
		BOOST_AUTO_TEST_CASE(Not_prime_end_number)
		{
			std::set<int> primeNumbers = GeneratePrimeNumbersSet(20);
			std::set<int> correctPrimeNumbersSet;
			correctPrimeNumbersSet.insert(2);
			correctPrimeNumbersSet.insert(3);
			correctPrimeNumbersSet.insert(5);
			correctPrimeNumbersSet.insert(7);
			correctPrimeNumbersSet.insert(11);
			correctPrimeNumbersSet.insert(13);
			correctPrimeNumbersSet.insert(17);
			correctPrimeNumbersSet.insert(19);
			BOOST_CHECK(correctPrimeNumbersSet == primeNumbers);
		}
		BOOST_AUTO_TEST_CASE(Prime_end_number)
		{
			std::set<int> primeNumbers = GeneratePrimeNumbersSet(19);
			std::set<int> correctPrimeNumbersSet;
			correctPrimeNumbersSet.insert(2);
			correctPrimeNumbersSet.insert(3);
			correctPrimeNumbersSet.insert(5);
			correctPrimeNumbersSet.insert(7);
			correctPrimeNumbersSet.insert(11);
			correctPrimeNumbersSet.insert(13);
			correctPrimeNumbersSet.insert(17);
			correctPrimeNumbersSet.insert(19);
			BOOST_CHECK(correctPrimeNumbersSet == primeNumbers);
		}
		BOOST_AUTO_TEST_CASE(Big_numbers_count)
		{
			std::set<int> primeNumbers = GeneratePrimeNumbersSet(100000000);
			BOOST_CHECK(primeNumbers.size() == 5761455);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()