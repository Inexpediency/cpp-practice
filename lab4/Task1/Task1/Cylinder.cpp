#include "stdafx.h"
#include "Cylinder.h"


double CCylinder::GetHeight() const
{
	return m_height;
}

double CCylinder::GetBaseRadius() const
{
	return m_baseRadius;
}

double CCylinder::GetVolume() const
{
	return m_baseRadius * m_baseRadius * M_PI * m_height * 2;
}

CCylinder::CCylinder(double density, double baseRadius, double height)
	:m_baseRadius(baseRadius), m_height(height)
{
	if (baseRadius <= 0)
	{
		throw std::invalid_argument("Can not to create cylinder with negative base radius");
	}
	if (height <= 0)
	{
		throw std::invalid_argument("Can not to create cylinder with negative base height");
	}
	if (density <= 0)
	{
		throw std::invalid_argument("Can not to create cylinder with negative density");
	}
	m_density = density;
}

std::string CCylinder::ToString() const
{
	std::string result = "Cylinder:";
	result = result + " mass = " + std::to_string(GetMass()) + ",";
	result = result + " density = " + std::to_string(GetDensity()) + ",";
	result = result + " volume = " + std::to_string(GetVolume()) + ",";
	result = result + " base radius = " + std::to_string(GetBaseRadius()) + ",";
	result = result + " height = " + std::to_string(GetHeight());
	return result;
}

bool CCylinder::operator==(const CCylinder & arg) const
{
	return (arg.GetDensity() == GetDensity()) &&
		(arg.GetMass() == GetMass()) &&
		(arg.GetVolume() == GetVolume()) &&
		(arg.GetBaseRadius() == GetBaseRadius()) &&
		(arg.GetHeight() == GetHeight());
}