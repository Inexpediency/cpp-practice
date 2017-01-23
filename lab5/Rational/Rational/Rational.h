#pragma once
#include <iostream>

class CRational
{
public:
	// ������������ ������������ �����, ������ ���� (0/1)
	CRational() = default;

	// ������������ ������������ �����, ������ value (value/1)
	CRational(int value);

	// ������������ ������������ �����, ������ numerator/denominator
	// ������������ ����� ������ ��������� � ��������������� ����:
	//	����������� ������������� (��������� ����� ���� �������������)
	//	��������� � ����������� �� ����� ����� ��������� (6/8 => 3/4 � �.�.)
	// ���� ����������� ����� ����, ������ ����������������� ������������ �����, ������ ����
	CRational(int numerator, int denominator);

	// ���������� ������������� ������������� ����� � ���� ��������� �����
	std::pair<int, CRational> ToCompoundFraction()const;

	// ���������� ���������
	int GetNumerator()const;

	// ���������� ����������� (����������� �����)
	int GetDenominator()const;

	// ���������� ��������� ��������� � ����������� � ���� ����� double
	double ToDouble()const;
	friend bool operator==(const CRational & number1, const CRational & number2);
	friend bool operator!=(const CRational & number1, const CRational & number2);
	friend bool operator<=(const CRational & number1, const CRational & number2);
	friend bool operator<(const CRational & number1, const CRational & number2);
	friend bool operator>=(const CRational & number1, const CRational & number2);
	friend bool operator>(const CRational & number1, const CRational & number2);
	friend std::istream & operator>>(std::istream & is, CRational & number);
	friend std::ostream & operator<<(std::ostream & os, const CRational & number);
	CRational operator-() const;
	CRational operator+() const;
	friend CRational operator+(const CRational & number1, const CRational & number2);
	friend CRational operator-(const CRational & number1, const CRational & number2);
	friend CRational operator*(const CRational & number1, const CRational & number2);
	friend CRational operator/(const CRational & number1, const CRational & number2);
	CRational & operator+=(const CRational & number);
	CRational & operator-=(const CRational & number);
	CRational & operator*=(const CRational & number);
	CRational & operator/=(const CRational & number);
private:
	int m_numerator = 0;
	unsigned int m_denominator = 1;
};
