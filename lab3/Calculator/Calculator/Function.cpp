#include "stdafx.h"
#include "Function.h"
#include "Variable.h"

CFunction::CFunction(const std::vector<std::shared_ptr<CVariable>> & dependentVariables, const std::shared_ptr<CValueHolder> & argument1, const std::shared_ptr<CValueHolder> & argument2, const std::string & operation)
	: m_dependentVariables(dependentVariables),
	m_operation(operation)
{
	m_arguments.first = argument1;
	m_arguments.second = argument2;
	Calc();
}

void CFunction::Calc()
{
	if (m_arguments.second == nullptr)
	{
		m_value = m_arguments.first->GetValue();
	}
	else
	{
		m_value = OPERATIONS.at(m_operation)(m_arguments.first->GetValue(), m_arguments.second->GetValue());
	}
}

void CFunction::Clear()
{
	m_dependentVariables.clear();
	m_arguments.first = nullptr;
	m_arguments.second = nullptr;
}

std::vector<std::shared_ptr<CVariable>> CFunction::GetDependentVariables()
{
	return m_dependentVariables;
}
