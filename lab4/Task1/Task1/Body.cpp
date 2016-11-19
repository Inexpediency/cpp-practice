#include "stdafx.h"
#include "Body.h"

double CBody::GetMass() const
{
	return GetDensity() * GetVolume();
}

double CBody::GetDensity() const
{
	return m_density;
}

std::string CBody::ToString() const
{
	std::string result = "Body:";
	result = result + " mass = " + std::to_string(GetMass()) + ",";
	result = result + " density = " + std::to_string(GetDensity()) + ",";
	result = result + " volume = " + std::to_string(GetVolume());
	return result;
}