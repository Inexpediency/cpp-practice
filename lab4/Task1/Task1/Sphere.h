#pragma once
#include "Body.h"
#include "SolidBody.h"

class CSphere :
	public CEqualityComparable<CBody, CSphere>, public CSolidBody
{
public:
	CSphere() = delete;
	CSphere(double density, double radius);
	double GetVolume() const;
	double GetRadius() const;
	bool operator==(const CSphere & arg) const;
protected:
	std::string NameToString() const override;
	std::string FieldsToString() const override;
private:
	double m_radius = NAN;
};