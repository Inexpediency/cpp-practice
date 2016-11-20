#include "stdafx.h"
#include "Compound.h"

double CCompound::GetMass() const
{
	return m_mass;
}

double CCompound::GetVolume() const
{
	return m_volume;
}

double CCompound::GetDensity() const
{
	return GetMass() / GetVolume();
}

bool CCompound::IsEmpty() const
{
	return m_children.empty();
}

bool CCompound::HasChild(CBody * child) const
{
	if (child == this)
	{
		return true;
	}
	for (auto & element : m_children)
	{
		if (element->HasChild(child))
		{
			return true;
		}
	}
	return false;
}

bool CCompound::AddChild(std::shared_ptr<CBody> childBody)
{
	if (!childBody->HasChild(this))
	{
		m_children.emplace_back(childBody);
		m_mass += childBody->GetMass();
		m_volume += childBody->GetVolume();
		return true;
	}
	return false;
}

std::string CCompound::ToString() const
{
	std::string result = "Compound:\n";	
	for (auto & element : m_children)
	{
		std::string elementStr = element->ToString();
		elementStr = std::regex_replace(elementStr, std::regex("^"), "  ");
		result = result + elementStr + "\n";
	}
	return result;
}