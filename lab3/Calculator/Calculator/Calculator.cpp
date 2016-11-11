#include "stdafx.h"
#include "Calculator.h"
#include "Variable.h"
#include "Function.h"

void CheckIdentifire(const std::string & ident)
{
	if (!std::regex_match(ident, std::regex("\\w(\\w|\\d)*")))
	{
		throw std::invalid_argument(ident + " is not identifire");
	}
}

void CCalculator::AddVariable(const std::string & name, const double & value)
{
	CheckIdentifire(name);
	if (m_variables.find(name) == m_variables.cend())
	{
		std::shared_ptr<CVariable> newVariable = std::make_shared<CVariable>();
		newVariable->SetValue(value);
		m_variables[name] = newVariable;
	}
	else
	{
		throw std::logic_error("Variable " + name + " already exist");
	}
}

void CCalculator::AddVariable(const std::string & name, const std::string & ident)
{
	CheckIdentifire(name);
	CheckIdentifire(ident);
	if (m_variables.find(name) == m_variables.cend())
	{
		std::shared_ptr<CVariable> newVariable = std::make_shared<CVariable>();
		std::shared_ptr<Valuabal> initElement = GetElement(ident);
		if (initElement == nullptr)
		{
			throw std::logic_error("There are no variable with name " + ident);
		}
		newVariable->SetValue(initElement->GetValue());
		m_variables[name] = newVariable;
	}
	else
	{
		throw std::logic_error("Variable " + name + " already exist");
	}
}

std::vector<std::shared_ptr<CVariable>> CCalculator::GetDependentVariablesList(const std::string & ident) const
{
	std::vector<std::shared_ptr<CVariable>> dependVariablesList;
	auto variableIter = m_variables.find(ident);
	auto functionIter = m_functions.find(ident);
	if (variableIter != m_variables.cend())
	{
		dependVariablesList.push_back(variableIter->second);
	}
	else if (functionIter != m_functions.cend())
	{
		auto variables = functionIter->second->GetDependentVariables();
		dependVariablesList.insert(dependVariablesList.cend(), variables.cbegin(), variables.cend());
	}
	else
	{
		throw std::invalid_argument("There are no variable or function with name " + ident);
	}
	return dependVariablesList;
}

std::shared_ptr<Valuabal> CCalculator::GetElement(const std::string & ident) const
{
	auto variableIter = m_variables.find(ident);
	auto functionIter = m_functions.find(ident);
	if (variableIter != m_variables.cend())
	{
		return variableIter->second;
	}
	else if (functionIter != m_functions.cend())
	{
		return functionIter->second;
	}
	else
	{
		return nullptr;
	}
}

std::vector<std::shared_ptr<CVariable>> MergePtrVectors(const std::vector<std::shared_ptr<CVariable>> & vector1, const std::vector<std::shared_ptr<CVariable>> & vector2)
{
	std::vector<std::shared_ptr<CVariable>> result(vector1);
	for (auto element : vector2)
	{
		if (!std::any_of(result.cbegin(), result.cend(), [element](std::shared_ptr<CVariable> el) { return el == element; }))
		{
			result.insert(result.cend(), element);
		}
	}
	return result;
}

void CCalculator::AddFunction(const std::string & name, const std::string & firstArgumentIdent, const std::string & secondArgumentIdent, const std::string & operation)
{
	CheckIdentifire(name);
	CheckIdentifire(firstArgumentIdent);
	if (m_functions.find(name) == m_functions.cend())
	{
		std::vector<std::shared_ptr<CVariable>> dependentVariables = GetDependentVariablesList(firstArgumentIdent);
		std::shared_ptr<Valuabal> argument1 = GetElement(firstArgumentIdent);
		std::shared_ptr<Valuabal> argument2 = nullptr;
		if (secondArgumentIdent != "")
		{
			CheckIdentifire(secondArgumentIdent);
			auto secondArgumentDependentVariables = GetDependentVariablesList(secondArgumentIdent);
			argument2 = GetElement(secondArgumentIdent);
			dependentVariables = MergePtrVectors(dependentVariables, secondArgumentDependentVariables);
		}
		std::shared_ptr<CFunction> newFunction = std::make_shared<CFunction>(dependentVariables, argument1, argument2, operation);
		m_functions[name] = newFunction;
		for (auto element : dependentVariables)
		{
			element->AppendDependentFunctions(newFunction);
		}
	}
	else
	{
		throw std::invalid_argument("Function " + name + " already exist");
	}
}

void CCalculator::SetVariableValue(const std::string & name, const double & value)
{
	auto variableIter = m_variables.find(name);
	if (variableIter != m_variables.cend())
	{
		variableIter->second->SetValue(value);
	}
	else
	{
		throw std::invalid_argument("There are no variable or function with name " + name);
	}
}

void CCalculator::SetVariableValue(const std::string & name, const std::string & ident)
{
	auto variableIter = m_variables.find(name);
	if (variableIter != m_variables.cend())
	{
		std::shared_ptr<Valuabal> initElement = GetElement(ident);
		if (initElement == nullptr)
		{
			throw std::logic_error("Can not find variable " + ident);
		}
		variableIter->second->SetValue(initElement->GetValue());
	}
	else
	{
		throw std::invalid_argument("There are no variable or function with name " + name);
	}
}

void CCalculator::PrintElement(std::ostream & output, const std::string & name) const
{
	auto element = GetElement(name);
	if (element != nullptr)
	{
		output << name << ": " << std::fixed << element->GetValue() << std::endl;
	}
	else
	{
		throw std::invalid_argument("There are no variable or function with name " + name);
	}
}

void CCalculator::PrintFunctions(std::ostream & output) const
{
	for (auto element : m_functions)
	{
		output << element.first << ": " << std::fixed << element.second->GetValue() << std::endl;
	}
}

void CCalculator::PrintVariables(std::ostream & output) const
{
	for (auto element : m_variables)
	{
		output << element.first << ": " << std::fixed << element.second->GetValue() << std::endl;
	}
}