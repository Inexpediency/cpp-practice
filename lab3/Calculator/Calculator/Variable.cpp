#include "stdafx.h"
#include "Variable.h"
#include "Function.h"

void CVariable::SetValue(double value)
{
	m_value = value;
	for (auto element : m_dependentFunctions)
	{
		element->Calc();
	}
}

void CVariable::AppendDependentFunctions(std::shared_ptr<CFunction> function)
{
	if (function != nullptr)
	{
		m_dependentFunctions.insert(m_dependentFunctions.cend(), function);
	}
	else
	{
		throw std::logic_error("Can not append nullptr to CFunctions list in CVariable");
	}
}