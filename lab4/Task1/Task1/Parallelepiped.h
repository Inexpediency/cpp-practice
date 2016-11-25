#pragma once
#include "Body.h"

class CParallelepiped : public CBody
{
public:
	CParallelepiped() = delete;
	CParallelepiped(double density, double width, double height, double depth);
	std::string ToString() const;
	double GetVolume() const;
	double GetHeight() const;
	double GetWidth() const;
	double GetDepth() const;
	bool IsEqual(CBody * element) const;
	bool operator==(const CParallelepiped & arg) const;
private:
	double m_width = NAN;
	double m_height = NAN;
	double m_depth = NAN;
};