#pragma once
#include <vector>
#include "Body.h"
class CCompound : public CEqualityComparable<CBody, CCompound>
{
public:
	double GetVolume() const;
	double GetMass() const;
	double GetDensity() const;
	bool AddChild(const std::shared_ptr<CBody> & childBody);
	std::string ToString() const;
	bool IsEmpty() const;
	bool HasChild(CBody * child) const;
	bool HasEqual(CBody * child) const;
	size_t GetChildCount() const;
	bool operator==(const CCompound & arg) const;
private:
	std::vector<std::shared_ptr<CBody>> m_children;
	double m_volume = 0;
	double m_mass = 0;
};