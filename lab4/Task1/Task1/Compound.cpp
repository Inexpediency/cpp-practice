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
	if (childBody != nullptr && !childBody->HasChild(this))
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

unsigned int CCompound::GetChildCount() const
{
	return m_children.size();
}

bool CCompound::IsEqual(CBody * element) const
{
	try
	{
		CCompound & compoundElement = dynamic_cast<CCompound &>(*element);
		return compoundElement == *this;
	}
	catch (std::bad_cast &)
	{
		return false;
	}
}

bool CCompound::HasEquel(CBody * child) const
{	
	for (auto element : m_children)
	{
		if (element->IsEqual(child))
		{
			return true;
		}
	}
	return false;
}

bool CCompound::operator==(const CCompound & arg) const
{
	if (m_children.size() == arg.GetChildCount())
	{
		for (auto element : m_children)
		{
			if (!arg.HasEquel(element.get()))
			{
				return false;
			}
		}
		return true;
	}
	return false;
}