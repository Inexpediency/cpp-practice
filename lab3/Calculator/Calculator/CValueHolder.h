#pragma once
#include <map>
#include <vector>
#include <string>
#include <functional>
#include "constants.h"

class CValueHolder
{
public:
	double GetValue() const;
	~CValueHolder() = default;
protected:
	double m_value;
};