#include "stdafx.h"
#include "../PrimeNumbers/prime_nubers_utils.h"

BOOST_AUTO_TEST_SUITE(Test_GeneratePrimeNumbers)
	BOOST_AUTO_TEST_SUITE(Find_all_prime_numbers_test)
		std::set<int> correctPrimeNumbersSet({ 2, 3, 5, 7, 11, 13, 17, 19 });
		BOOST_AUTO_TEST_CASE(Not_prime_end_number)
		{
			std::set<int> primeNumbers = GeneratePrimeNumbersSet(20);
			BOOST_CHECK(correctPrimeNumbersSet == primeNumbers);
		}
		BOOST_AUTO_TEST_CASE(Start_value)
		{
			std::set<int> primeNumbers = GeneratePrimeNumbersSet(0);
			std::set<int> correctSet;
			BOOST_CHECK(correctSet == primeNumbers);
			primeNumbers = GeneratePrimeNumbersSet(1);
			BOOST_CHECK(correctSet == primeNumbers);
			primeNumbers = GeneratePrimeNumbersSet(2);
			correctSet.insert(2);
			BOOST_CHECK(correctSet == primeNumbers);
		}
		BOOST_AUTO_TEST_CASE(Prime_end_number)
		{
			std::set<int> primeNumbers = GeneratePrimeNumbersSet(19);
			BOOST_CHECK(correctPrimeNumbersSet == primeNumbers);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()