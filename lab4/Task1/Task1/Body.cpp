#include "stdafx.h"
#include "Body.h"

double CBody::GetMass() const
{
	return GetDensity() * GetVolume();
}

std::string CBody::NameToString() const
{
	return "Body:";
}

std::string CBody::FieldsToString() const
{
	return "";
}

bool CBody::IsCanAddedToCompound(CCompound * compound) const
{
	return true;
}

bool CBody::SetParent(CCompound * compound)
{
	return true;
}

std::string CBody::ToString() const
{
	std::string result = NameToString();
	result = result + " mass = " + std::to_string(GetMass()) + ",";
	result = result + " density = " + std::to_string(GetDensity()) + ",";
	result = result + " volume = " + std::to_string(GetVolume());
	result = result + FieldsToString();
	return result;
}