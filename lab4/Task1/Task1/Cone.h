#pragma once
#include "Body.h"

class CCone : public CEqualityComparable<CBody, CCone>
{
public:
	CCone() = delete;
	CCone(double density, double baseRadius, double height);
	std::string ToString() const;
	double GetVolume() const;
	double GetHeight() const;
	double GetBaseRadius() const;
	bool operator==(const CCone & arg) const;
private:
	double m_height = NAN;
	double m_baseRadius = NAN;
};