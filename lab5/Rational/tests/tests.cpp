#include "stdafx.h"
#include "../Rational/Rational.h"

struct RationalFixture
{
	CRational number;
};

BOOST_AUTO_TEST_SUITE(Rational_can_be_created_by)
	BOOST_AUTO_TEST_CASE(default_construcor)
	{
		CRational number = CRational();
		BOOST_CHECK_EQUAL(number.GetNumerator(), 0);
		BOOST_CHECK_EQUAL(number.GetDenominator(), 1);
	}
	BOOST_AUTO_TEST_CASE(int_value)
	{
		CRational number = CRational(10);
		BOOST_CHECK_EQUAL(number.GetNumerator(), 10);
		BOOST_CHECK_EQUAL(number.GetDenominator(), 1);
	}

	BOOST_AUTO_TEST_CASE(denominator_and_numerator)
	{
		CRational number = CRational(11, 15);
		BOOST_CHECK_EQUAL(number.GetNumerator(), 11);
		BOOST_CHECK_EQUAL(number.GetDenominator(), 15);
		number = CRational(10, 5);
		BOOST_CHECK_EQUAL(number.GetNumerator(), 2);
		BOOST_CHECK_EQUAL(number.GetDenominator(), 1);
		number = CRational(-10, -5);
		BOOST_CHECK_EQUAL(number.GetNumerator(), 2);
		BOOST_CHECK_EQUAL(number.GetDenominator(), 1);
		number = CRational(-10, 5);
		BOOST_CHECK_EQUAL(number.GetNumerator(), -2);
		BOOST_CHECK_EQUAL(number.GetDenominator(), 1);
		number = CRational(10, -5);
		BOOST_CHECK_EQUAL(number.GetNumerator(), -2);
		BOOST_CHECK_EQUAL(number.GetDenominator(), 1);
	}

	BOOST_AUTO_TEST_CASE(throw_exeption_if_denominator_equal_zero)
	{
		CRational number = CRational(10);
		BOOST_CHECK_THROW(CRational(-10, 0), std::logic_error);
	}

	struct RationalFixture
	{
		CRational number = CRational(-11, 19);
		CRational number1 = CRational(1, 2);
	};
	BOOST_FIXTURE_TEST_SUITE(on_create, RationalFixture)
		BOOST_AUTO_TEST_CASE(can_be_converted_to_double)
		{
			BOOST_CHECK_EQUAL(number.ToDouble(), (double)(-11) / (double)(19));
		}

		BOOST_AUTO_TEST_CASE(can_be_converted_to_compound_fraction)
		{
			std::pair<int, CRational> result = CRational(10, 4).ToCompoundFraction();
			BOOST_CHECK_EQUAL(result.first,  2);
			BOOST_CHECK_EQUAL(result.second, CRational(1, 2));

			result = CRational(1, 4).ToCompoundFraction();
			BOOST_CHECK_EQUAL(result.first, 0);
			BOOST_CHECK_EQUAL(result.second, CRational(1, 4));

			result = CRational(-10, 4).ToCompoundFraction();
			BOOST_CHECK_EQUAL(result.first, -2);
			BOOST_CHECK_EQUAL(result.second, CRational(1, 2));
		}

		BOOST_AUTO_TEST_CASE(can_be_printed_in_stream)
		{
			std::stringstream output;
			output << number;
			BOOST_CHECK_EQUAL(output.str(), "-11/19");
		}

		BOOST_AUTO_TEST_CASE(can_be_read_from_stream)
		{
			std::stringstream input;
			input.str("-11/19");
			input >> number;
			BOOST_CHECK_EQUAL(number.ToDouble(), CRational(-11, 19).ToDouble());
		}

		BOOST_AUTO_TEST_CASE(can_be_compared)
		{
			BOOST_CHECK(number == CRational(-11, 19));
			BOOST_CHECK(number != CRational(11, 19));
			BOOST_CHECK(number1 <= CRational(1, 2));
			BOOST_CHECK(number1 <= 1);
			BOOST_CHECK(number1 < 1);
			BOOST_CHECK(number1 > 0);
			BOOST_CHECK(1 >= number1);
			BOOST_CHECK(1 > number1);
			BOOST_CHECK(0 < number1);
			BOOST_CHECK(number1 > CRational(-1, 2));
			BOOST_CHECK(number1 >= CRational(1, 2));
			BOOST_CHECK(number1 >= CRational(-1, 2));
		}

		BOOST_AUTO_TEST_CASE(can_change_sign_by_unary_minus)
		{
			BOOST_CHECK_EQUAL(-number, CRational(11, 19));
			BOOST_CHECK_EQUAL(-number1, CRational(-1, 2));
		}

		BOOST_AUTO_TEST_CASE(can_use_unary_plus)
		{
			BOOST_CHECK_EQUAL(+number, CRational(-11, 19));
			BOOST_CHECK_EQUAL(+number1, CRational(1, 2));
		}

		BOOST_AUTO_TEST_SUITE(can_be_added_by)
			BOOST_AUTO_TEST_CASE(other_Rational)
			{
				BOOST_CHECK_EQUAL(number + CRational(11, 19), 0);
				BOOST_CHECK_EQUAL(number1 + CRational(1, 6), CRational(2, 3));
			}
			BOOST_AUTO_TEST_CASE(int_)
			{
				BOOST_CHECK_EQUAL(number1 + 1, CRational(3, 2));
				BOOST_CHECK_EQUAL(1 + number1, CRational(3, 2));
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(can_be_deducted_by)
			BOOST_AUTO_TEST_CASE(other_Rational)
			{
				BOOST_CHECK_EQUAL(number - CRational(-11, 19), 0);
				BOOST_CHECK_EQUAL(number1 - CRational(1, 6), CRational(1, 3));
			}
			BOOST_AUTO_TEST_CASE(int_)
			{
				BOOST_CHECK_EQUAL(number1 - 1, CRational(-1, 2));
				BOOST_CHECK_EQUAL(1 - number1, CRational(1, 2));
			}
		BOOST_AUTO_TEST_SUITE_END()
		
		BOOST_AUTO_TEST_SUITE(can_be_multyply_by)
			BOOST_AUTO_TEST_CASE(other_Rational)
			{
				BOOST_CHECK_EQUAL(number1 * CRational(2, 3), CRational(1, 3));
			}
			BOOST_AUTO_TEST_CASE(int_)
			{
				BOOST_CHECK_EQUAL(number1 * (-3), CRational(-3, 2));
				BOOST_CHECK_EQUAL(7 * CRational(2, 3), CRational(14, 3));
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(can_be_devided_by)
			BOOST_AUTO_TEST_CASE(other_Rational)
			{
				BOOST_CHECK_EQUAL(number1 / CRational(2, 3), CRational(3, 4));
			}
			BOOST_AUTO_TEST_CASE(int_)
			{
				BOOST_CHECK_EQUAL(number1 / 5, CRational(1, 10));
				BOOST_CHECK_EQUAL(7 / CRational(2, 3), CRational(21, 2));
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(can_be_added_and_assign_by)
			BOOST_AUTO_TEST_CASE(other_Rational)
			{
				number += CRational(11, 19);
				BOOST_CHECK_EQUAL(number, 0);
				number1 += CRational(1, 6);
				BOOST_CHECK_EQUAL(number1, CRational(2, 3));
			}
			BOOST_AUTO_TEST_CASE(int_)
			{
				number1 += 1;
				BOOST_CHECK_EQUAL(number1, CRational(3, 2));
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(can_be_deducted_and_assign_by)
			BOOST_AUTO_TEST_CASE(other_Rational)
			{
				number -= CRational(-11, 19);
				BOOST_CHECK_EQUAL(number, 0);
				number1 -= CRational(1, 6);
				BOOST_CHECK_EQUAL(number1, CRational(1, 3));
			}
			BOOST_AUTO_TEST_CASE(int_)
			{
				number1 -= 1;
				BOOST_CHECK_EQUAL(number1, CRational(-1, 2));
			}
		BOOST_AUTO_TEST_SUITE_END()


		BOOST_AUTO_TEST_SUITE(can_be_multyply_and_assigned_by)
			BOOST_AUTO_TEST_CASE(other_Rational)
			{
				number1 *= CRational(2, 3);
				BOOST_CHECK_EQUAL(number1, CRational(1, 3));
			}
			BOOST_AUTO_TEST_CASE(int_)
			{
				number1 *= (-3);
				BOOST_CHECK_EQUAL(number1, CRational(-3, 2));
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(can_be_devided_and_assigned_by)
			BOOST_AUTO_TEST_CASE(other_Rational)
			{
				number1 /= CRational(2, 3);
				BOOST_CHECK_EQUAL(number1, CRational(3, 4));
			}
			BOOST_AUTO_TEST_CASE(int_)
			{
				number1 /= 5;
				BOOST_CHECK_EQUAL(number1, CRational(1, 10));
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()