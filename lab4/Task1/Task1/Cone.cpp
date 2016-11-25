#include "stdafx.h"
#include "Cone.h"


double CCone::GetHeight() const
{
	return m_height;
}

double CCone::GetBaseRadius() const
{
	return m_baseRadius;
}

double CCone::GetVolume() const
{
	return m_baseRadius * m_baseRadius * M_PI * m_height / 3;
}

CCone::CCone(double density, double baseRadius, double height)
	:m_baseRadius(baseRadius), m_height(height)
{
	if (baseRadius <= 0)
	{
		throw std::invalid_argument("Can not to create cone with negative base radius");
	}
	if (height <= 0)
	{
		throw std::invalid_argument("Can not to create cone with negative base height");
	}
	if (density <= 0)
	{
		throw std::invalid_argument("Can not to create cone with negative density");
	}
	m_density = density;
}

std::string CCone::ToString() const
{
	std::string result = "Cone:";
	result = result + " mass = " + std::to_string(GetMass()) + ",";
	result = result + " density = " + std::to_string(GetDensity()) + ",";
	result = result + " volume = " + std::to_string(GetVolume()) + ",";
	result = result + " base radius = " + std::to_string(GetBaseRadius()) + ",";
	result = result + " height = " + std::to_string(GetHeight());
	return result;
}

bool CCone::IsEqual(CBody * element) const
{
	try
	{
		CCone & coneElement = dynamic_cast<CCone &>(*element);
		return coneElement == *this;
	}
	catch (std::bad_cast &)
	{
		return false;
	}
}

bool CCone::operator==(const CCone & arg) const
{
	return (arg.GetDensity() == GetDensity()) && 
		(arg.GetMass() == GetMass()) &&
		(arg.GetVolume() == GetVolume()) &&
		(arg.GetBaseRadius() == GetBaseRadius()) && 
		(arg.GetHeight() == GetHeight());
}