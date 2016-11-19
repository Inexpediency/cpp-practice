#pragma once
#include "Body.h"

class CCylinder : public CBody
{
public:
	CCylinder() = delete;
	CCylinder(double density, double baseRadius, double height);
	std::string ToString() const;
	double GetVolume() const;
	double GetHeight() const;
	double GetBaseRadius() const;
private:
	double m_height = NAN;
	double m_baseRadius = NAN;
};