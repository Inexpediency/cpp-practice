#include "stdafx.h"
#include "../FindAndReplace/replace_utils.h"


BOOST_AUTO_TEST_SUITE(ReplaceTests)

BOOST_AUTO_TEST_CASE(CorrectReplace)
{
	{
		std::string subject = "abcdefg";
		std::string replace = "b";
		std::string search = "a";
		BOOST_CHECK(FindAndReplace(subject, search, replace) == "bbcdefg");
	}
	
	{
		std::string subject = "abcdefg";
		std::string replace = "b";
		std::string search = "ab";
		BOOST_CHECK(FindAndReplace(subject, search, replace) == "bcdefg");
	}

	{
		std::string subject = "abcdefg";
		std::string replace = "ab";
		std::string search = "a";
		BOOST_CHECK(FindAndReplace(subject, search, replace) == "abbcdefg");
	}

	{
		std::string subject = "abcdefg";
		std::string replace = "";
		std::string search = "a";
		BOOST_CHECK(FindAndReplace(subject, search, replace) == "bcdefg");
	}
}

BOOST_AUTO_TEST_SUITE_END()