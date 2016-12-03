#pragma once
#include "Body.h"

class CSolidBody : virtual public CBody
{
public:
	double GetDensity() const override
	{
		return m_density;
	}
protected:
	double m_density = NAN;
};