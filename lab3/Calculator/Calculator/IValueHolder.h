#pragma once
#include <map>
#include <vector>
#include <string>
#include <functional>
#include "constants.h"

class IValueHolder
{
public:
	double GetValue() const;
	~IValueHolder() = default;
protected:
	double m_value;
};