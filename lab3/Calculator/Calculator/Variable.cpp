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

void CVariable::AppendDependentFunctions(const std::shared_ptr<CFunction> & function)
{
	m_dependentFunctions.push_back(function);
}