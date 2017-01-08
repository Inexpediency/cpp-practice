#include "stdafx.h"
#include "../find_max_ex/find_max_func.h"

struct SSportsman
{
	std::string name;
	int width;
	int height;
};

bool IsLessWidth(SSportsman const& lhs, SSportsman const& rhs)
{
	return (lhs.width < rhs.width);
}

bool IsLessHeight(SSportsman const& lhs, SSportsman const& rhs)
{
	return (lhs.height < rhs.height);
}

const SSportsman Andrew = { "Andrew", 84, 197 };
const SSportsman Artyom = { "Artyom", 70, 185 };
const SSportsman Nick = { "Nick", 53, 184 };
const SSportsman Misha = { "Misha", 71, 181 };
const SSportsman Ramil = { "Ramil", 90, 180 };
const SSportsman Vasya = { "Vasya", 80, 172 };

const std::vector<SSportsman> sportsmen = {
	Andrew, Artyom, Nick, Misha, Ramil, Vasya
};

void VerifySportsman(SSportsman const& rhs, SSportsman const& lhs)
{
	BOOST_CHECK_EQUAL(lhs.name, rhs.name);
	BOOST_CHECK_EQUAL(lhs.height, rhs.height);
	BOOST_CHECK_EQUAL(lhs.width, rhs.width);
}

BOOST_AUTO_TEST_SUITE(FindMaxFunction)

BOOST_AUTO_TEST_CASE(not_find_in_empty_vector)
{
	int max = 42;
	BOOST_CHECK(!FindMax({}, max));
	BOOST_CHECK_EQUAL(max, 42);
}

BOOST_AUTO_TEST_CASE(can_find_max_element_in_not_empty_vector)
{
	{
		int max = 0;
		BOOST_CHECK(FindMax({ 3, 4, 2, 1, 5 }, max));
		BOOST_CHECK_EQUAL(max, 5);
	}

	{
		int max = 0;
		BOOST_CHECK(FindMax({ 3, 4, 2, 5, 1 }, max, [](const auto lhs, const auto rhs) {
			return (lhs < (rhs * 6));
		}));
		BOOST_CHECK_EQUAL(max, 1);
	}

	{
		SSportsman theHeaviestSportsman;
		BOOST_CHECK(FindMax(sportsmen, theHeaviestSportsman, IsLessWidth));
		VerifySportsman(theHeaviestSportsman, Ramil);
	}

	{
		SSportsman theHighestSportsman;
		BOOST_CHECK(FindMax(sportsmen, theHighestSportsman, IsLessHeight));
		VerifySportsman(theHighestSportsman, Andrew);
	}
}

BOOST_AUTO_TEST_SUITE_END()