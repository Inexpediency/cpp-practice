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

std::string CCone::NameToString() const
{
	return "Cone:";
}

std::string CCone::FieldsToString() const
{
	std::string result;
	result = result + ", base radius = " + std::to_string(GetBaseRadius()) + ",";
	result = result + " height = " + std::to_string(GetHeight());
	return result;
}

bool CCone::operator==(const CCone & arg) const
{
	return (arg.GetDensity() == GetDensity()) && 
		(arg.GetMass() == GetMass()) &&
		(arg.GetVolume() == GetVolume()) &&
		(arg.GetBaseRadius() == GetBaseRadius()) && 
		(arg.GetHeight() == GetHeight());
}