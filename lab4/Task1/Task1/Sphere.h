#pragma once
#include "Body.h"

class CSphere : public CEqualityComparable<CBody, CSphere>
{
public:
	CSphere() = delete;
	CSphere(double density, double radius);
	std::string ToString() const;
	double GetVolume() const;
	double GetRadius() const;
	bool operator==(const CSphere & arg) const;
private:
	double m_radius = NAN;
};