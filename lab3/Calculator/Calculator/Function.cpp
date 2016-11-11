#include "stdafx.h"
#include "Function.h"
#include "Variable.h"

CFunction::CFunction(const std::vector<std::shared_ptr<CVariable>> & dependentVariables, std::shared_ptr<Valuabal> argument1, std::shared_ptr<Valuabal> argument2, const std::string & operation)
	: m_dependentVariables(dependentVariables),
	m_operation(operation)
{
	m_arguments.first = argument1;
	m_arguments.second = argument2;
	Calc();
}

void CFunction::Calc()
{
	if (m_arguments.first == nullptr)
	{
		throw std::invalid_argument("First element in m_arguments pair can not be nullptr");
	}
	if (OPERATIONS.find(m_operation) == OPERATIONS.cend())
	{
		throw std::invalid_argument("There are no such operation " + m_operation);
	}
	if (m_arguments.second == nullptr)
	{
		m_value = m_arguments.first->GetValue();
	}
	else
	{
		m_value = OPERATIONS.at(m_operation)(m_arguments.first->GetValue(), m_arguments.second->GetValue());
	}
}

std::vector<std::shared_ptr<CVariable>> CFunction::GetDependentVariables()
{
	return m_dependentVariables;
}
