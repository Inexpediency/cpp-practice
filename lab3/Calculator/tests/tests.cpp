#include "stdafx.h"
#include <boost/test/output_test_stream.hpp> 

#include "../Calculator/Calculator.h"
#include "../Calculator/CValueHolder.h"
#include "../Calculator/print_utils.h"
#include <functional>

typedef boost::test_tools::output_test_stream boost_test_stream;

bool IsNan(const double & numeric)
{
	return numeric != numeric;
}

struct CalculatorFixture
{
	CCalculator calc;
};

BOOST_FIXTURE_TEST_SUITE(Calculator, CalculatorFixture)
	BOOST_AUTO_TEST_CASE(on_create_empty)
	{
		BOOST_CHECK(calc.GetVars().empty());
		BOOST_CHECK(calc.GetFuncs().empty());
	}
	BOOST_AUTO_TEST_CASE(can_declare_new_variable)
	{
		calc.AddVariable("x");
		auto vars = calc.GetVars();
		BOOST_CHECK(vars.find("x") != vars.end());
	}
	BOOST_AUTO_TEST_CASE(can_declare_new_variable_with_start_value)
	{
		calc.AddVariable("x", 1);
		calc.AddVariable("y", "x");
		BOOST_CHECK_EQUAL(calc.GetElement("x")->GetValue(), 1);
		BOOST_CHECK_EQUAL(calc.GetElement("y")->GetValue(), 1);
	}
	BOOST_AUTO_TEST_CASE(can_not_declare_variable_started_by_number)
	{
		BOOST_CHECK(calc.GetVars().empty());
		BOOST_CHECK_THROW(calc.AddVariable("5x"), std::logic_error);
	}
	BOOST_AUTO_TEST_CASE(can_not_declare_a_variable_for_the_second_time)
	{
		calc.AddVariable("x");
		BOOST_CHECK_THROW(calc.AddVariable("x"), std::logic_error);
	}
	BOOST_AUTO_TEST_CASE(throw_exeption_if_try_to_set_value_for_not_created_function)
	{
		BOOST_CHECK_THROW(calc.SetVariableValue("x", 1), std::logic_error);
		calc.AddVariable("x");
		BOOST_CHECK_THROW(calc.SetVariableValue("Y", "x"), std::logic_error);
	}
	struct _when_variable_create : CalculatorFixture
	{
		_when_variable_create()
		{
			calc.AddVariable("var1");
			calc.AddVariable("var2");
		}
	};
	BOOST_FIXTURE_TEST_SUITE(when_variable_create, _when_variable_create)
		BOOST_AUTO_TEST_CASE(default_variable_value_is_nan)
		{
			BOOST_CHECK(IsNan(calc.GetElement("var1")->GetValue()));
		}
		BOOST_AUTO_TEST_CASE(can_set_variable_value)
		{
			calc.SetVariableValue("var1", 1);
			BOOST_CHECK_EQUAL(calc.GetElement("var1")->GetValue(), 1);
		}
		BOOST_AUTO_TEST_CASE(can_not_set_varible_value_by_has_not_created_function)
		{
			BOOST_CHECK_THROW(calc.SetVariableValue("var1", "didnotCreatedFunc"), std::logic_error);
		}
		struct _when_variable_is_seted_value : _when_variable_create
		{
			_when_variable_is_seted_value()
			{
				calc.SetVariableValue("var1", 1);
				calc.SetVariableValue("var2", 2);
			}
		};
		BOOST_FIXTURE_TEST_SUITE(when_variable_is_seted_value, _when_variable_is_seted_value)
			BOOST_AUTO_TEST_CASE(can_change_variable_value_by_double_value)
			{
				calc.SetVariableValue("var1", 2);
				BOOST_CHECK_EQUAL(calc.GetElement("var1")->GetValue(), 2);
			}
			BOOST_AUTO_TEST_CASE(can_change_variable_value_by_double_value_fn_value)
			{
				calc.AddFunction("SayVar1Value", "var1");
				calc.SetVariableValue("var2", "SayVar1Value");
				BOOST_CHECK_EQUAL(calc.GetElement("var2")->GetValue(), 1);
				calc.SetVariableValue("var1", 2);
				BOOST_CHECK_EQUAL(calc.GetElement("SayVar1Value")->GetValue(), 2);
				BOOST_CHECK_EQUAL(calc.GetElement("var2")->GetValue(), 1);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_CASE(can_create_a_function)
	{
		calc.AddVariable("var1", 1);
		calc.AddVariable("var2", 2);
		calc.AddFunction("SayVar1Value", "var1");
		BOOST_CHECK_EQUAL(calc.GetElement("SayVar1Value")->GetValue(), 1);
		calc.AddFunction("fib3", "var1", "var2", "+");
		BOOST_CHECK_EQUAL(calc.GetElement("fib3")->GetValue(), 3);
	}
	BOOST_AUTO_TEST_CASE(can_not_create_function_with_incorrect_parametrs)
	{
		calc.AddVariable("var1");
		BOOST_CHECK_THROW(calc.AddFunction("var1", "var1"), std::logic_error);
		BOOST_CHECK_THROW(calc.AddFunction("Fn", ""), std::logic_error);
		BOOST_CHECK_THROW(calc.AddFunction("Fn", "var1", "var2", "1"), std::logic_error);
	}
	BOOST_AUTO_TEST_CASE(can_not_create_function_that_already_created)
	{
		calc.AddVariable("var1");
		calc.AddFunction("SayVar1Value", "var1");
		BOOST_CHECK_THROW(calc.AddFunction("SayVar1Value", "var1"), std::invalid_argument);
	}

	struct _when_function_created : CalculatorFixture
	{
		_when_function_created()
		{
			calc.AddVariable("var1", 1);
			calc.AddVariable("var2", 2);
			calc.AddVariable("varNan");
			calc.AddFunction("fn1", "var1");
			calc.AddFunction("fn2", "var2", "var1", "-");
			calc.AddFunction("fn3", "var2", "var1", "*");
			calc.AddFunction("fn4", "var2", "var1", "/");
			calc.AddFunction("fnNan", "varNan");
		}
	};
	BOOST_FIXTURE_TEST_SUITE(when_function_created, _when_function_created)
		BOOST_AUTO_TEST_CASE(change_value_when_base_variable_change_value)
		{
			BOOST_CHECK_EQUAL(calc.GetElement("fn1")->GetValue(), 1);
			BOOST_CHECK_EQUAL(calc.GetElement("fn2")->GetValue(), 1);
			calc.SetVariableValue("var1", 2);
			BOOST_CHECK_EQUAL(calc.GetElement("fn1")->GetValue(), 2);
			BOOST_CHECK_EQUAL(calc.GetElement("fn2")->GetValue(), 0);
			calc.SetVariableValue("var2", 4);
			BOOST_CHECK_EQUAL(calc.GetElement("fn3")->GetValue(), 8);
			BOOST_CHECK_EQUAL(calc.GetElement("fn4")->GetValue(), 2);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

struct CalculatorFixtureForPrint : CalculatorFixture
{
	CalculatorFixtureForPrint()
	{
		calc.AddVariable("var1", 1);
		calc.AddVariable("var2", 2);
		calc.AddVariable("varNan");
		calc.AddFunction("fn1", "var1");
		calc.AddFunction("fn2", "var2", "var1", "-");
		calc.AddFunction("fn3", "var2", "var1", "*");
		calc.AddFunction("fn4", "var2", "var1", "/");
		calc.AddFunction("fnNan", "varNan");
	}
};

BOOST_FIXTURE_TEST_SUITE(Calculator_can_be_printed, CalculatorFixtureForPrint)
	BOOST_AUTO_TEST_CASE(element)
	{
		boost_test_stream output("VarOut.txt", true);
		PrintElement(output, calc, "var1");
		BOOST_CHECK(output.match_pattern());
		boost_test_stream output1("FnOut.txt", true);
		PrintElement(output1, calc, "fn1");
		BOOST_CHECK(output1.match_pattern());
		boost_test_stream output3("NanOut.txt", true);
		PrintElement(output3, calc, "varNan");
		PrintElement(output3, calc, "fnNan");
		BOOST_CHECK(output3.match_pattern());
		BOOST_CHECK_THROW(PrintElement(output3, calc, "not_created_element"), std::logic_error);
	}
	BOOST_AUTO_TEST_CASE(variables)
	{
		boost_test_stream output("VarsOut.txt", true);
		PrintVariables(output, calc);
		BOOST_CHECK(output.match_pattern());
	}
	BOOST_AUTO_TEST_CASE(functions)
	{
		boost_test_stream output("FnsOut.txt", true);
		PrintFunctions(output, calc);
		BOOST_CHECK(output.match_pattern());
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(StressTestCalculator)
	BOOST_AUTO_TEST_CASE(fib_numbers)
	{
		CCalculator calc = CCalculator();
		calc.AddVariable("fib0", 1);
		calc.AddVariable("fib1", 1);
		double temp;
		double fibNumb1 = 1;
		double fibNumb2 = 1;
		for (auto i = 2; i <= 1000; ++i)
		{
			temp = fibNumb2;
			fibNumb2 = fibNumb2 + fibNumb1;
			fibNumb1 = temp;
			calc.AddFunction("fib" + std::to_string(i), "fib" + std::to_string(i - 1), "fib" + std::to_string(i - 2), "+");
			auto iFibValue = calc.GetElement("fib" + std::to_string(i))->GetValue();
			BOOST_CHECK_EQUAL(iFibValue, fibNumb2);
		}
	}
BOOST_AUTO_TEST_SUITE_END()