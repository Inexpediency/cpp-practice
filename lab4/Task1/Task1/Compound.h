#pragma once
#include <vector>
#include "Body.h"
class CCompound : public CEqualityComparable<CBody, CCompound>
{
public:
	double GetVolume() const override;
	double GetMass() const override;
	double GetDensity() const override;
	bool AddChild(const std::shared_ptr<CBody> & childBody);
	bool IsEmpty() const;
	bool HasEqual(CBody * child) const;
	size_t GetChildCount() const;
	bool operator==(const CCompound & arg) const;
	CCompound * GetParent() const;
	bool SetParent(CCompound * compound) override;
	bool IsCanAddedToCompound(CCompound * compound) const override;
protected:
	std::string NameToString() const override;
	std::string FieldsToString() const override;
private:
	CCompound * m_parent;
	std::vector<std::shared_ptr<CBody>> m_children;
	double m_volume = 0;
	double m_mass = 0;
	
};