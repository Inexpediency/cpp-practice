#pragma once
#include "Body.h"

class CSphere : public CBody
{
public:
	CSphere() = delete;
	CSphere(double density, double radius);
	std::string ToString() const;
	double GetVolume() const;
	double GetRadius() const;
private:
	double m_radius = NAN;
};