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


bool CCompound::SetParent(CCompound * compound)
{
	if (m_parent == nullptr)
	{
		m_parent = compound;
		return true;
	}
	return false;
}

CCompound * CCompound::GetParent() const
{
	return m_parent;
}

bool CCompound::IsCanAddedToCompound(CCompound * compound) const
{
	auto currentChild = compound;
	while (currentChild)
	{
		if (currentChild == this)
		{
			return false;
		}
		currentChild = currentChild->GetParent();
	}
	return true;
}

bool CCompound::AddChild(const std::shared_ptr<CBody> & childBody)
{
	if (childBody != nullptr && childBody->SetParent(this) && childBody->IsCanAddedToCompound(this))
	{
		m_children.emplace_back(childBody);
		m_mass += childBody->GetMass();
		m_volume += childBody->GetVolume();
		return true;
	}
	return false;
}

std::string CCompound::NameToString() const
{
	return "Compound:\n";
}

std::string CCompound::FieldsToString() const
{
	std::string result = "\n";
	for (auto & element : m_children)
	{
		std::string elementStr = element->ToString();
		elementStr = std::regex_replace(elementStr, std::regex("^"), "  ");
		result = result + elementStr + "\n";
	}
	return result;
}

size_t CCompound::GetChildCount() const
{
	return m_children.size();
}

bool CCompound::HasEqual(CBody * child) const
{	
	for (auto element : m_children)
	{
		return std::any_of(m_children.cbegin(), m_children.cend(), [&child](const auto & element){
			return element->IsEqual(*child);
		});
	}
	return false;
}

bool CCompound::operator==(const CCompound & arg) const
{
	if (m_children.size() == arg.GetChildCount())
	{
		return std::all_of(m_children.cbegin(), m_children.cend(), [&arg](const auto & element)
		{
			return arg.HasEqual(element.get());
		});
	}
	return false;
}