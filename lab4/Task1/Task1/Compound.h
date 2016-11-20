#pragma once
#include <vector>
#include "Body.h"
class CCompound : public CBody
{
public:
	double GetVolume() const;
	double GetMass() const;
	double GetDensity() const;
	bool AddChild(std::shared_ptr<CBody> childBody);
	std::string ToString() const;
	bool CCompound::IsEmpty() const;
	bool CCompound::HasChild(CBody * child) const;
private:
	std::vector<std::shared_ptr<CBody>> m_children;
	double m_volume = 0;
	double m_mass = 0;
};