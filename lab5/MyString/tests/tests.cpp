#include "stdafx.h"
#include "../MyString/MyString.h"

BOOST_AUTO_TEST_SUITE(My_string)
	BOOST_AUTO_TEST_CASE(can_be_init_by_string_constant)
	{
		CMyString string("Some string");
		BOOST_CHECK_EQUAL(string.GetStringData(), "Some string");
	}
	BOOST_AUTO_TEST_CASE(can_be_init_by_nullptr)
	{
		CMyString string(nullptr);
		BOOST_CHECK_EQUAL(string.GetStringData(), "");
	}
	BOOST_AUTO_TEST_CASE(can_be_init_by_string_with_zero_symblo)
	{
		char a[] = "This is the string with \0 symbol";
		CMyString string(a, strlen(a) + 7);
		BOOST_CHECK(memcmp(string.GetStringData(), a, sizeof(a)));
		CMyString string1("", 0);
		BOOST_CHECK_EQUAL(string1.GetStringData(), "");
	}
	BOOST_AUTO_TEST_CASE(can_be_init_by_other_object_MyString_class)
	{
		CMyString other("Some string");
		CMyString string(other);
		BOOST_CHECK_EQUAL(string.GetStringData(), "Some string");
		BOOST_CHECK(string.GetStringData() != other.GetStringData());
	}
	BOOST_AUTO_TEST_CASE(can_be_init_by_other_rlink_of_MyString_class)
	{
		CMyString string(CMyString("Some string"));
		BOOST_CHECK_EQUAL(string.GetStringData(), "Some string");
	}
	BOOST_AUTO_TEST_CASE(can_be_init_by_stl_string)
	{
		std::string stlString("Some string");
		CMyString string(stlString);
		BOOST_CHECK_EQUAL(string.GetStringData(), "Some string");
	}
	struct MyStringFixture
	{
		MyStringFixture()
		{
			string = CMyString("Some long string");
		}
		CMyString string;
	};
	BOOST_FIXTURE_TEST_SUITE(MyString_on_create, MyStringFixture)
		BOOST_AUTO_TEST_CASE(can_be_cleared)
		{
			string.Clear();
			BOOST_CHECK_EQUAL(string.GetStringData(), "\0");
		}
		BOOST_AUTO_TEST_SUITE(can_be_assigned_by)
			BOOST_AUTO_TEST_CASE(constant_char_pointer)
			{
				string = "Some string";
				BOOST_CHECK_EQUAL("Some string", string.GetStringData());
			}
			BOOST_AUTO_TEST_CASE(empty_string)
			{
				CMyString emptyString = CMyString();
				string = emptyString;
				BOOST_CHECK_EQUAL(CMyString().GetStringData(), string.GetStringData());
			}
			BOOST_AUTO_TEST_CASE(MyString)
			{
				CMyString other("Some string");
				string = other;
				BOOST_CHECK_EQUAL(other.GetStringData(), string.GetStringData());
			}
			BOOST_AUTO_TEST_CASE(itself)
			{
				string = string;
				BOOST_CHECK_EQUAL("Some long string", string.GetStringData());
			}
			BOOST_AUTO_TEST_CASE(rLink)
			{
				CMyString string1("string1");
				string = std::move(string1);
				CMyString string2;
				string2 = std::move(string1);
				BOOST_CHECK_EQUAL(string.GetStringData(), "string1");
				BOOST_CHECK_EQUAL(string2.GetStringData(), "");
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(can_be_split_into_substring)
			BOOST_AUTO_TEST_CASE(if_arguments_correct_return_substr)
			{
				CMyString substring = string.SubString(5, 4);
				BOOST_CHECK_EQUAL(substring.GetStringData(), "long");
			}
			BOOST_AUTO_TEST_CASE(if_arguments_incorrect_return_empty_string)
			{
				CMyString substring = string.SubString(20, 2);
				BOOST_CHECK_EQUAL(substring.GetStringData(), "");
			}
			BOOST_AUTO_TEST_CASE(if_second_argument_bigger_then_string_length)
			{
				CMyString substring = string.SubString(0, 20);
				BOOST_CHECK_EQUAL(substring.GetStringData(), "Some long string");
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(can_be_concat_with)
			BOOST_AUTO_TEST_CASE(constant_char_pointer)
			{
				string = string + " with extra word";
				BOOST_CHECK_EQUAL("Some long string with extra word", string.GetStringData());
			}
			BOOST_AUTO_TEST_CASE(empty_string)
			{
				CMyString copy(string);
				string = string + CMyString();
				BOOST_CHECK_EQUAL(copy.GetStringData(), string.GetStringData());
			}
			BOOST_AUTO_TEST_CASE(MyString)
			{
				CMyString other(" with extra word");
				string = string + other;
				BOOST_CHECK_EQUAL("Some long string with extra word", string.GetStringData());
			}
			BOOST_AUTO_TEST_CASE(itself)
			{
				string = string + string;
				BOOST_CHECK_EQUAL("Some long stringSome long string", string.GetStringData());
			}
			BOOST_AUTO_TEST_CASE(rLink)
			{
				string = string + std::move(CMyString(" with extra rLink word"));
				BOOST_CHECK_EQUAL("Some long string with extra rLink word", string.GetStringData());
			}
			BOOST_AUTO_TEST_CASE(stl_string)
			{
				string = string + std::string(" with extra word");
				BOOST_CHECK_EQUAL("Some long string with extra word", string.GetStringData());
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(can_be_concat_by_plus_assign_operator_with)
			BOOST_AUTO_TEST_CASE(constant_char_pointer)
			{
				string += " with extra word";
				BOOST_CHECK_EQUAL("Some long string with extra word", string.GetStringData());
			}
			BOOST_AUTO_TEST_CASE(empty_string)
			{
				CMyString copy(string);
				string += CMyString();
				BOOST_CHECK_EQUAL(copy.GetStringData(), string.GetStringData());
			}
			BOOST_AUTO_TEST_CASE(MyString)
			{
				CMyString other(" with extra word");
				string += other;
				BOOST_CHECK_EQUAL("Some long string with extra word", string.GetStringData());
			}
			BOOST_AUTO_TEST_CASE(itself)
			{
				string += string;
				BOOST_CHECK_EQUAL("Some long stringSome long string", string.GetStringData());
			}
			BOOST_AUTO_TEST_CASE(rLink)
			{
				string += std::move(CMyString(" with extra rLink word"));
				BOOST_CHECK_EQUAL("Some long string with extra rLink word", string.GetStringData());
			}
			BOOST_AUTO_TEST_CASE(stl_string)
			{
				string += std::string(" with extra word");
				BOOST_CHECK_EQUAL("Some long string with extra word", string.GetStringData());
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_CASE(can_return_value_by_index)
		{
			BOOST_CHECK_EQUAL(string[0], 'S');
		}
		BOOST_AUTO_TEST_CASE(can_change_value_by_index)
		{
			string[0] = 's';
			BOOST_CHECK_EQUAL(string[0], 's');
		}
		BOOST_AUTO_TEST_CASE(throw_exeption_if_out_of_range_when_get_value_by_index)
		{
			const CMyString constString(string);
			BOOST_CHECK_THROW(constString[string.GetLength()], std::exception);
			BOOST_CHECK_THROW(string[string.GetLength()], std::exception);
		}
		BOOST_AUTO_TEST_SUITE(can_be_compeared_with)
			BOOST_AUTO_TEST_CASE(constant_char_pointer)
			{
				BOOST_CHECK("Some long string" == string);
				BOOST_CHECK("Some ShortString" != string);
				BOOST_CHECK("Some other long string" != string);
			}
			BOOST_AUTO_TEST_CASE(MyString)
			{
				CMyString other("Some other long string");
				BOOST_CHECK(other != string);
				other = "Some long string";
				BOOST_CHECK(other == string);
			}
			BOOST_AUTO_TEST_CASE(itself)
			{
				BOOST_CHECK(string == string);
			}
			BOOST_AUTO_TEST_CASE(stl_string)
			{
				std::string other("Some other long string");
				BOOST_CHECK(other != string);
				other = "Some long string";
				BOOST_CHECK(other == string);
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(can_be_compared_by_less_operator_with)
			BOOST_AUTO_TEST_CASE(constant_char_pointer)
			{
				BOOST_CHECK("Some long string" <= string);
				BOOST_CHECK("Some long alert" <= string);
				BOOST_CHECK("Some long" <= string);
				BOOST_CHECK(!("Some long string e" <= string));
				BOOST_CHECK("Some long" < string);
				BOOST_CHECK("Some long alert" < string);
				BOOST_CHECK(!("Some long zebra " < string));
				BOOST_CHECK(!("Some long string" < string));
				BOOST_CHECK(!("Some long string e" < string));
			}
			BOOST_AUTO_TEST_CASE(MyString)
			{
				CMyString other("Some long string");
				BOOST_CHECK(other <= string);
				other = "Some long";
				BOOST_CHECK(other <= string);
				other = "Some long string e";
				BOOST_CHECK(!(other <= string));
				other = "Some long";
				BOOST_CHECK(other < string);
				other = "Some long string";
				BOOST_CHECK(!(other < string));
				other = "Some long string e";
				BOOST_CHECK(!(other < string));
			}
			BOOST_AUTO_TEST_CASE(itself)
			{
				BOOST_CHECK(string <= string);
				BOOST_CHECK(!(string < string));
			}
			BOOST_AUTO_TEST_CASE(stl_string)
			{
				std::string other("Some long string");
				BOOST_CHECK(other <= string);
				other = "Some long";
				BOOST_CHECK(other <= string);
				other = "Some long string e";
				BOOST_CHECK(!(other <= string));
				other = "Some long";
				BOOST_CHECK(other < string);
				other = "Some long string";
				BOOST_CHECK(!(other < string));
				other = "Some long string e";
				BOOST_CHECK(!(other < string));
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(can_be_compared_by_more_operator_with)
			BOOST_AUTO_TEST_CASE(constant_char_pointer)
			{
				BOOST_CHECK("Some long string" >= string);
				BOOST_CHECK("Some long zebra string" > string);
				BOOST_CHECK(!("Some long" >= string));
				BOOST_CHECK("Some long string e" >= string);
				BOOST_CHECK(!("Some long" > string));
				BOOST_CHECK("Some long zebra string" > string);
				BOOST_CHECK(!("Some long string" > string));
				BOOST_CHECK("Some long string e" > string);
			}
			BOOST_AUTO_TEST_CASE(MyString)
			{
				CMyString other("Some long string");
				BOOST_CHECK(other >= string);
				other = "Some long";
				BOOST_CHECK(!(other >= string));
				other = "Some long string e";
				BOOST_CHECK(other >= string);
				other = "Some long";
				BOOST_CHECK(!(other > string));
				other = "Some long string";
				BOOST_CHECK(!(other > string));
				other = "Some long string e";
				BOOST_CHECK(other > string);
			}
			BOOST_AUTO_TEST_CASE(itself)
			{
				BOOST_CHECK(string >= string);
				BOOST_CHECK(!(string > string));
			}
			BOOST_AUTO_TEST_CASE(stl_string)
			{
				std::string other("Some long string");
				BOOST_CHECK(other >= string);
				other = "Some long";
				BOOST_CHECK(!(other >= string));
				other = "Some long string e";
				BOOST_CHECK(other >= string);
				other = "Some long";
				BOOST_CHECK(!(other > string));
				other = "Some long string";
				BOOST_CHECK(!(other > string));
				other = "Some long string e";
				BOOST_CHECK(other > string);
			}
		BOOST_AUTO_TEST_SUITE_END()
	
		BOOST_AUTO_TEST_CASE(can_create_iterator_to_begin_of_string)
		{
			auto it = string.begin();
			BOOST_CHECK(*it == 'S');
		}
		BOOST_AUTO_TEST_CASE(can_create_constant_iterator_to_begin_of_string)
		{
			auto it = string.cbegin();
			BOOST_CHECK(*it == 'S');
		}
		BOOST_AUTO_TEST_CASE(can_create_iterator_to_end_of_string)
		{
			auto it = string.end();
			BOOST_CHECK_THROW(*it, std::exception);
		}
		BOOST_AUTO_TEST_CASE(can_create_constant_iterator_to_end_of_string)
		{
			auto it = string.cend();
			BOOST_CHECK_THROW(*it, std::exception);
		}
		BOOST_AUTO_TEST_CASE(can_use_in_range_based_for)
		{
			size_t len = 0;
			for (auto ch : string)
			{
				++len;
			}
			BOOST_CHECK_EQUAL(string.GetLength(), len);
		}
		struct MyStringIteratorFixture
		{
			CMyString string = CMyString("Some line");
			CMyString::CIterator<char> itBegin = string.begin();
			CMyString::CIterator<char> itEnd = string.end();
		};
		BOOST_FIXTURE_TEST_SUITE(MyString_iterator_on_create, MyStringIteratorFixture)
			BOOST_AUTO_TEST_CASE(can_be_compeared)
			{
				BOOST_CHECK(itBegin == string.begin());
				BOOST_CHECK(itBegin != itEnd);
			}
			BOOST_AUTO_TEST_CASE(can_be_incremented)
			{
				BOOST_CHECK_EQUAL(*(++itBegin), 'o');
				BOOST_CHECK_EQUAL(*(itBegin++), 'o');
				BOOST_CHECK_EQUAL(*itBegin, 'm');
			}
			BOOST_AUTO_TEST_CASE(throw_exeption_if_out_of_range_by_increment)
			{
				BOOST_CHECK_THROW(itEnd++, std::exception);
			}
			BOOST_AUTO_TEST_CASE(can_be_decrease_by_another_iterator)
			{
				BOOST_CHECK_EQUAL(itEnd - itBegin, string.GetLength());
				BOOST_CHECK_THROW(itBegin - itEnd, std::logic_error);
			}
			BOOST_AUTO_TEST_CASE(can_be_decremented)
			{
				BOOST_CHECK_EQUAL(*(--itEnd), 'e');
				BOOST_CHECK_EQUAL(*(itEnd--), 'e');
				BOOST_CHECK_EQUAL(*itEnd, 'n');
			}
			BOOST_AUTO_TEST_CASE(throw_exeption_if_out_of_range_by_decrement)
			{
				BOOST_CHECK_THROW(itBegin--, std::exception);
			}
			BOOST_AUTO_TEST_CASE(can_be_increase_by_index)
			{
				BOOST_CHECK_EQUAL(*(itBegin + 1), 'o');
			}
			BOOST_AUTO_TEST_CASE(throw_exeption_if_out_of_range_by_increase)
			{
				BOOST_CHECK_THROW(itEnd + 1, std::exception);
			}
			BOOST_AUTO_TEST_CASE(can_be_decrease_by_index)
			{
				BOOST_CHECK_EQUAL(*(itEnd - 1), 'e');
			}
			BOOST_AUTO_TEST_CASE(throw_exeption_if_out_of_range_by_decrease)
			{
				BOOST_CHECK_THROW(itBegin - 1, std::exception);
			}
			BOOST_AUTO_TEST_CASE(can_be_assigned_with_increasing)
			{
				itBegin += 1;
				BOOST_CHECK_EQUAL(*itBegin, 'o');
			}
			BOOST_AUTO_TEST_CASE(throw_exeption_if_out_of_range_by_assigned_with_increasing)
			{
				BOOST_CHECK_THROW(itEnd += 1, std::exception);
			}
			BOOST_AUTO_TEST_CASE(can_be_assigned_with_decreasing)
			{
				itEnd -= 1;
				BOOST_CHECK_EQUAL(*itEnd, 'e');
			}
			BOOST_AUTO_TEST_CASE(throw_exeption_if_out_of_range_by_assigned_with_decreasing)
			{
				BOOST_CHECK_THROW(itBegin -= 1, std::exception);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()