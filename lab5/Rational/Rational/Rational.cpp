#include "stdafx.h"
#include "Rational.h"

CRational::CRational(int value)
	: m_numerator(value) {};

CRational::CRational(int numerator, int denominator)
{
	if (denominator == 0)
	{
		throw std::logic_error("Can not create rational with denominator 0");
	}
	int commonGCD = boost::math::gcd(numerator, denominator);
	m_numerator = numerator / commonGCD * boost::math::sign(denominator);
	m_denominator = denominator / commonGCD * boost::math::sign(denominator);
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return (double)m_numerator / (double)m_denominator;
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	std::pair<int, CRational> compoundFraction;
	compoundFraction.first = (m_numerator - m_numerator % (int)m_denominator) / (int)m_denominator;
	compoundFraction.second = CRational(m_numerator % m_denominator, m_denominator);
	return compoundFraction;
}

bool operator==(const CRational & number1, const CRational & number2)
{
	return number1.m_numerator == number2.m_numerator && number1.m_denominator == number2.m_denominator;
}
bool operator!=(const CRational & number1, const CRational & number2)
{
	return !(number1 == number2);
}
bool operator<=(const CRational & number1, const CRational & number2)
{
	return (number1.m_numerator * (int)number2.m_denominator) <= (number2.m_numerator * (int)number1.m_denominator);
}
bool operator<(const CRational & number1, const CRational & number2)
{
	return (number1.m_numerator * (int)number2.m_denominator) < (number2.m_numerator * (int)number1.m_denominator);
}
bool operator>=(const CRational & number1, const CRational & number2)
{
	return number2 <= number1;
}
bool operator>(const CRational & number1, const CRational & number2)
{
	return number2 < number1;
}

std::istream & operator>> (std::istream & is, CRational & number)
{
	is >> number.m_numerator;
	is >> number.m_denominator;
	return is;
}
std::ostream & operator<< (std::ostream & os, const CRational & number)
{
	os << std::to_string(number.m_numerator) << "/" << std::to_string(number.m_denominator);
	return os;
}

CRational CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}
CRational CRational::operator+() const
{
	return CRational(m_numerator, m_denominator);
}

CRational operator+(const CRational & number1, const CRational & number2)
{
	int numerator = number1.m_numerator * number2.m_denominator + number2.m_numerator * number1.m_denominator;
	unsigned int denominator = number1.m_denominator * number2.m_denominator;
	return CRational(numerator, denominator);
}
CRational operator-(const CRational & number1, const CRational & number2)
{
	int numerator = number1.m_numerator * number2.m_denominator - number2.m_numerator * number1.m_denominator;
	unsigned int denominator = number1.m_denominator * number2.m_denominator;
	return CRational(numerator, denominator);
}

CRational operator*(const CRational & number1, const CRational & number2)
{
	int numerator = number1.m_numerator * number2.m_numerator;
	unsigned int denominator = number1.m_denominator * number2.m_denominator;
	return CRational(numerator, denominator);
}
CRational operator/(const CRational & number1, const CRational & number2)
{
	int numerator = number1.m_numerator * number2.m_denominator;
	unsigned int denominator = number1.m_denominator * number2.m_numerator;
	return CRational(numerator, denominator);
}

CRational & CRational::operator+=(const CRational & number)
{
	*this = *this + number;
	return *this;
}
CRational & CRational::operator-=(const CRational & number)
{
	*this = *this - number;
	return *this;
}

CRational & CRational::operator*=(const CRational & number)
{
	*this = *this * number;
	return *this;
}
CRational & CRational::operator/=(const CRational & number)
{
	*this = *this / number;
	return *this;
}