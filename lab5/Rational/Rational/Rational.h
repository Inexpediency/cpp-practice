#pragma once
#include <iostream>

class CRational
{
public:
	//  онструирует рациональное число, равное нулю (0/1)
	CRational() = default;

	//  онструирует рациональное число, равное value (value/1)
	CRational(int value);

	//  онструирует рациональное число, равное numerator/denominator
	// –ациональное число должно хранитьс€ в нормализованном виде:
	//	знаменатель положительный (числитель может быть отрицательным)
	//	числитель и знаменатель не имеют общиз делителей (6/8 => 3/4 и т.п.)
	// ≈сли знаменатель равен нулю, должно сконструироватьс€ рациональное число, равное нулю
	CRational(int numerator, int denominator);

	// ¬озвращает представление рационального числа в виде смешанной дроби
	std::pair<int, CRational> ToCompoundFraction()const;

	// ¬озвращает числитель
	int GetNumerator()const;

	// ¬озвращает знаменатель (натуральное число)
	int GetDenominator()const;

	// ¬озвращает отношение числител€ и знаменател€ в виде числа double
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
