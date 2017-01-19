#include "stdafx.h"
#include "Calculator.h"
#include "Variable.h"
#include "Function.h"

void ÑheckIdentifireForError(const std::string & ident)
{
	if (!std::regex_match(ident, std::regex("^[a-zA-Z_][a-zA-Z0-9_]*$")))
	{
		throw std::invalid_argument(ident + " is not identifire");
	}
}

void CCalculator::CheckIdentifire(const std::string & ident)
{
	ÑheckIdentifireForError(ident);
	if (GetElement(ident) != nullptr)
	{
		throw std::invalid_argument(ident + " already exist");
	}
}

void CCalculator::AddVariable(const std::string & name, const double & value)
{
	CheckIdentifire(name);
	std::shared_ptr<CVariable> newVariable = std::make_shared<CVariable>();
	newVariable->SetValue(value);
	m_variables[name] = newVariable;
}

void CCalculator::AddVariable(const std::string & name, const std::string & ident)
{
	CheckIdentifire(name);
	ÑheckIdentifireForError(ident);
	std::shared_ptr<CValueHolder> initElement = GetElement(ident);
	std::shared_ptr<CVariable> newVariable = std::make_shared<CVariable>();
	newVariable->SetValue(initElement->GetValue());
	m_variables[name] = newVariable;
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
	if (functionIter != m_functions.cend())
	{
		auto variables = functionIter->second->GetDependentVariables();
		dependVariablesList.insert(dependVariablesList.cend(), variables.cbegin(), variables.cend());
	}
	return dependVariablesList;
}

std::shared_ptr<CValueHolder> CCalculator::GetElement(const std::string & ident) const
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
	return nullptr;
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
	ÑheckIdentifireForError(firstArgumentIdent);
	if (OPERATIONS.find(operation) == OPERATIONS.cend())
	{
		throw std::logic_error("thera are not such operators");
	}
	std::vector<std::shared_ptr<CVariable>> dependentVariables = GetDependentVariablesList(firstArgumentIdent);
	std::shared_ptr<CValueHolder> argument1 = GetElement(firstArgumentIdent);
	std::shared_ptr<CValueHolder> argument2 = nullptr;
	if (secondArgumentIdent != "")
	{
		ÑheckIdentifireForError(secondArgumentIdent);
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
		std::shared_ptr<CValueHolder> initElement = GetElement(ident);
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

std::map<std::string, std::shared_ptr<CVariable>> CCalculator::GetVars() const
{
	return m_variables;
}


std::map<std::string, std::shared_ptr<CFunction>> CCalculator::GetFuncs() const
{
	return m_functions;
}

void CCalculator::PrintElement(std::ostream & output, const std::string & name) const
{
	auto element = GetElement(name);
	if (element != nullptr)
	{
		output << std::fixed;
		output << std::setprecision(2);
		double value = element->GetValue();
		if (isnan(value))
		{
			output << name << ":nan" << std::endl;
		}
		else
		{
			output << name << ":" << value << std::endl;
		}
	}
	else
	{
		throw std::invalid_argument("There are no variable or function with name " + name);
	}
}

void CCalculator::PrintFunctions(std::ostream & output) const
{
	output << std::fixed; 
	output << std::setprecision(2);
	for (auto element : m_functions)
	{
		double value = element.second->GetValue();
		if (isnan(value))
		{
			output << element.first << ":nan" << std::endl;
		}
		else
		{
			output << element.first << ":" << value << std::endl;
		}
	}
}

void CCalculator::PrintVariables(std::ostream & output) const
{
	output << std::fixed;
	output << std::setprecision(2);
	for (auto element : m_variables)
	{
		double value = element.second->GetValue();
		if (isnan(value))
		{
			output << element.first << ":nan" << std::endl;
		}
		else
		{
			output << element.first << ":" << value << std::endl;
		}
	}
}

CCalculator::~CCalculator()
{
	for (auto & el : m_functions)
	{
		el.second->Clear();
	}
	for (auto & el : m_functions)
	{
		el.second->Clear();
	}
}