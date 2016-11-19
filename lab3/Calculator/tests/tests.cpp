#include "stdafx.h"
#include "../Calculator/Calculator.h"
#include "../Calculator/IValueHolder.h"
#include "../Calculator/Variable.h"
#include "../Calculator/Function.h"

struct CalculatorFixture
{
	CCalculator calculator;
};

BOOST_FIXTURE_TEST_SUITE(On_create_calculator, CalculatorFixture)

	BOOST_AUTO_TEST_CASE(_have_no_function)
	{
		std::stringstream out;
		calculator.PrintFunctions(out);
		std::string result;
		out >> result;
		BOOST_CHECK_EQUAL(result, "");
	}

	BOOST_AUTO_TEST_CASE(_have_no_variables)
	{
		std::stringstream out;
		calculator.PrintVariables(out);
		std::string result;
		out >> result;
		BOOST_CHECK_EQUAL(result, "");
	}

	BOOST_AUTO_TEST_CASE(_can_add_variables)
	{
		try
		{
			calculator.AddVariable("x");
		}
		catch (std::exception & exception)
		{	
			BOOST_CHECK(0);
			std::cout << exception.what() << std::endl;
		}
	}

BOOST_AUTO_TEST_SUITE_END()