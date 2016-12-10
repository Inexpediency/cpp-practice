#pragma once
#include "Body.h"
#include "SolidBody.h"
class CCone : 
	public CEqualityComparable<CSolidBody, CCone>
{
public:
	CCone() = delete;
	CCone(double density, double baseRadius, double height);
	double GetVolume() const;
	double GetHeight() const;
	double GetBaseRadius() const;
	bool operator==(const CCone & arg) const;
protected:
	std::string NameToString() const override;
	std::string FieldsToString() const override;
private:
	double m_height = NAN;
	double m_baseRadius = NAN;
};