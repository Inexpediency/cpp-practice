#pragma once
#include "Body.h"

class CCone : public CBody
{
public:
	CCone() = delete;
	CCone(double density, double baseRadius, double height);
	std::string ToString() const;
	double GetVolume() const;
	double GetHeight() const;
	double GetBaseRadius() const; 
	bool IsEqual(CBody * element) const;
	bool operator==(const CCone & arg) const;
private:
	double m_height = NAN;
	double m_baseRadius = NAN;
};