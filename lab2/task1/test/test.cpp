#include "stdafx.h"
#include "../task1/vector_utils.h"

bool IsVectorsEquel(doubleVector vector1, doubleVector vector2)
{
	for (size_t i = 0; i < vector1.size(); ++i)
	{
		if (vector1[i] != vector2[i])
		{
			return false;
		}
	}
	return vector1.size() == vector2.size();
}

BOOST_AUTO_TEST_SUITE(DoubleVectorTest)

BOOST_AUTO_TEST_CASE(ReadCorrectVector)
{
	std::stringstream strstream("123.3 123.4 123.5");
	doubleVector correctVector = { 123.3, 123.4, 123.5 };
	doubleVector processingVector = { 123.3, 123.4, 123.5 };
	doubleVector readingVector = ReadVector(strstream);
	BOOST_CHECK(IsVectorsEquel(readingVector, correctVector));
}


BOOST_AUTO_TEST_CASE(ProcessVectorTest)
{
	doubleVector correctVector = { 4, -12, 8, -10 };
	doubleVector processingVector = { 2, -6, 4, -5 };
	ProcessVector(processingVector);
	PrintSortedVector(std::cout, processingVector);
	BOOST_CHECK(IsVectorsEquel(processingVector, correctVector));
}

BOOST_AUTO_TEST_SUITE_END()