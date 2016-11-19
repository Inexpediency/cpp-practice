#pragma once
#include <string>

class CBody
{
public:
	virtual double GetVolume() const = 0;
	virtual double GetMass() const;
	virtual double GetDensity() const;	
	virtual std::string ToString() const;
	virtual ~CBody() {};
protected:
	CBody() = default;
protected:
	double m_density = NAN;
};