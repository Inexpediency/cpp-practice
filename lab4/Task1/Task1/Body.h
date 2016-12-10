#pragma once
#include <string>
class CCompound;
class CBody;
template <typename Base, typename T>
class CEqualityComparable : virtual public Base
{
public:
	bool IsEqual(const CBody & body)const override
	{
		auto bodyAsT = dynamic_cast<const T*>(&body);
		auto selfAsT = static_cast<const T*>(this);
		return bodyAsT && *bodyAsT == *selfAsT;
	}
	virtual bool operator==(const T & rhs) const = 0;
};

class CBody
{
public:
	virtual bool IsEqual(const CBody & body) const = 0;
	virtual double GetVolume() const = 0;
	virtual double GetMass() const;
	virtual double GetDensity() const = 0;
	virtual bool SetParent(CCompound * compound = nullptr);
	virtual bool IsCanAddedToCompound(CCompound * compound = nullptr) const;
	virtual std::string ToString() const;
	virtual ~CBody() {};
protected:
	virtual std::string NameToString() const;
	virtual std::string FieldsToString() const;
};