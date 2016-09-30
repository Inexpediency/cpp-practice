#include "stdafx.h"
#include "../flip_byte/flip_byte_utils.h"

BOOST_AUTO_TEST_SUITE(InputDataTest)


BOOST_AUTO_TEST_CASE(IncorrectArgumentCount)
{
	char * strArr[] = { "", "123" };
    BOOST_CHECK(!CheckInput(1, strArr));
	BOOST_CHECK(!CheckInput(3, strArr));
}

BOOST_AUTO_TEST_CASE(IncorrectArgument)
{
	char * strArr[] = { "", "1234a" };
	BOOST_CHECK(!CheckInput(2, strArr));
	strArr[1] = "a3";
	BOOST_CHECK(!CheckInput(2, strArr));
	strArr[1] = "1234";
	BOOST_CHECK(!CheckInput(2, strArr));
}

BOOST_AUTO_TEST_CASE(CorrectData)
{
	char * strArr[] = {"", "123"};
	BOOST_CHECK(CheckInput(2, strArr));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(FlipByteTest)

BOOST_AUTO_TEST_CASE(NotFlipedNumber)
{
	BOOST_CHECK(FlipByte(126) == 126);
}

BOOST_AUTO_TEST_CASE(CorrectData)
{
	BOOST_CHECK(FlipByte(1) == 128);
	BOOST_CHECK(FlipByte(23) == 232);
}

BOOST_AUTO_TEST_SUITE_END()