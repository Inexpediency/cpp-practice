#pragma once
#include <string>

class CBody
{
public:
	virtual double GetVolume() const = 0;
	virtual double GetMass() const;
	virtual double GetDensity() const;
	virtual bool HasChild(CBody * child = nullptr) const;
	virtual std::string ToString() const;
	virtual ~CBody() {};
protected:
	double m_density = NAN;
};