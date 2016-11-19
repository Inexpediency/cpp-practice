#pragma once
#include <map>
#include <memory>
#include <vector>
#include <string>
#include "IValueHolder.h"

class CVariable;

class CFunction : public IValueHolder
{
public:
	CFunction() = delete;
	CFunction(const std::vector<std::shared_ptr<CVariable>> & dependentVariables, std::shared_ptr<IValueHolder> & argument1, std::shared_ptr<IValueHolder> & argument2, const std::string & operation);
	std::vector<std::shared_ptr<CVariable>> GetDependentVariables();
	void Calc();
private:
	std::vector<std::shared_ptr<CVariable>> m_dependentVariables;
	std::pair<std::shared_ptr<IValueHolder>, std::shared_ptr<IValueHolder>> m_arguments;
	std::string m_operation;
};