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

bool CCompound::IsSame(CBody & childBody) const
{
	//std::cout << "!!!!!" << (&childBody == this) << std::endl;
	if (this == &childBody)
	{
		return true;
	}
	/*std::shared_ptr<CCompound> compoundChild(dynamic_cast<CCompound *>(&childBody));
	if (compoundChild != nullptr)
	{
		for (auto & element : compoundChild->m_children)
		{
			if (IsSame(*element))
			{
				return true;
			}
		}
	}*/
	return false;
}

bool CCompound::AddChild(std::shared_ptr<CBody> childBody)
{
	if (!IsSame(*childBody))
	{
		m_children.emplace_back(childBody);
		m_mass += childBody->GetMass();
		m_volume += childBody->GetVolume();
		return true;
	}
	return false;
}

std::vector<std::shared_ptr<CBody>> CCompound::GetChildren() const
{
	return m_children;
}

std::string CCompound::ToString() const
{
	std::string result = "Compound:\n";
	for (auto & element : m_children)
	{
		result = result + "  " + element->ToString() + "\n";
	}
	return result;
}