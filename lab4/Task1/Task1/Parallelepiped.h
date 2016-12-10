#pragma once
#include "Body.h"
#include "SolidBody.h"

class CParallelepiped : 
	public CEqualityComparable<CSolidBody, CParallelepiped>
{
public:
	CParallelepiped() = delete;
	CParallelepiped(double density, double width, double height, double depth);
	double GetVolume() const;
	double GetHeight() const;
	double GetWidth() const;
	double GetDepth() const;
	bool operator==(const CParallelepiped & arg) const;
protected:
	std::string NameToString() const override;
	std::string FieldsToString() const override;
private:
	double m_width = NAN;
	double m_height = NAN;
	double m_depth = NAN;
};