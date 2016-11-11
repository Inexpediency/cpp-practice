#include "stdafx.h"
#include "../FindAndReplace/replace_utils.h"

BOOST_AUTO_TEST_SUITE(Test_FindAndReplace)

BOOST_AUTO_TEST_CASE(One_character_on_one_character_replace)
{
	{
		std::string subject = "abcdefg";
		std::string replace = "b";
		std::string search = "a";
		BOOST_CHECK_EQUAL(FindAndReplace(subject, search, replace), "bbcdefg");
	}

	{
		std::string subject = "abcdefg";
		std::string replace = "c";
		std::string search = "b";
		BOOST_CHECK_EQUAL(FindAndReplace(subject, search, replace), "accdefg");
	}

	{
		std::string subject = "abcdefg";
		std::string replace = "f";
		std::string search = "g";
		BOOST_CHECK_EQUAL(FindAndReplace(subject, search, replace), "abcdeff");
	}
}

BOOST_AUTO_TEST_CASE(One_character_on_many_characters_replace)
{
	{
		std::string subject = "replace Center char";
		std::string replace = "Char c";
		std::string search = "C";
		BOOST_CHECK_EQUAL(FindAndReplace(subject, search, replace), "replace Char center char");
	}

	{
		std::string subject = "Replace first char char";
		std::string replace = "Good r";
		std::string search = "R";
		BOOST_CHECK_EQUAL(FindAndReplace(subject, search, replace), "Good replace first char char");
	}

	{
		std::string subject = "Replace ending char C";
		std::string replace = "good";
		std::string search = "C";
		BOOST_CHECK_EQUAL(FindAndReplace(subject, search, replace), "Replace ending char good");
	}
}
BOOST_AUTO_TEST_CASE(Many_character_on_one_characters_replace)
{
	{
		std::string subject = "replace first word";
		std::string replace = "a";
		std::string search = "replace";
		BOOST_CHECK_EQUAL(FindAndReplace(subject, search, replace), "a first word");
	}

	{
		std::string subject = "replace center word";
		std::string replace = "c";
		std::string search = "center";
		BOOST_CHECK_EQUAL(FindAndReplace(subject, search, replace), "replace c word");
	}

	{
		std::string subject = "replace end word";
		std::string replace = "a";
		std::string search = "word";
		BOOST_CHECK_EQUAL(FindAndReplace(subject, search, replace), "replace end a");
	}
}

BOOST_AUTO_TEST_CASE(Many_character_on_many_characters_replace)
{
	{
		std::string subject = "first word replace";
		std::string replace = "good";
		std::string search = "first";
		BOOST_CHECK_EQUAL(FindAndReplace(subject, search, replace), "good word replace");
	}

	{
		std::string subject = "center word replace";
		std::string replace = "good";
		std::string search = "word";
		BOOST_CHECK_EQUAL(FindAndReplace(subject, search, replace), "center good replace");
	}

	{
		std::string subject = "end word replace";
		std::string replace = "good";
		std::string search = "replace";
		BOOST_CHECK_EQUAL(FindAndReplace(subject, search, replace), "end word good");
	}
}

BOOST_AUTO_TEST_SUITE_END()