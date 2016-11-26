#pragma once
#include <string>

template <typename Base, typename T>
class CEqualityComparable : public Base
{
public:
	bool IsEqual(const Base & body)const override
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
	virtual double GetDensity() const;
	virtual bool HasChild(CBody * child = nullptr) const;
	virtual std::string ToString() const;
	virtual ~CBody() {};
protected:
	double m_density = NAN;
};