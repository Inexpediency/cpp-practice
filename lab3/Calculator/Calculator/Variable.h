#pragma once
#include <vector>
#include <memory>
#include "CValueHolder.h"
#include "constants.h"

class CFunction;

class CVariable : public CValueHolder
{
public:
	CVariable() = default;
	void SetValue(double value);
	void AppendDependentFunctions(const std::shared_ptr<CFunction> & function);
private:
	std::vector<std::shared_ptr<CFunction>> m_dependentFunctions;
};