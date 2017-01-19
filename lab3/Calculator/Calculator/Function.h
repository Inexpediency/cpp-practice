#pragma once
#include <map>
#include <memory>
#include <vector>
#include <string>
#include "CValueHolder.h"

class CVariable;

class CFunction : public CValueHolder
{
public:
	CFunction() = delete;
	CFunction(const std::vector<std::shared_ptr<CVariable>> & dependentVariables, const std::shared_ptr<CValueHolder> & argument1, const std::shared_ptr<CValueHolder> & argument2, const std::string & operation);
	std::vector<std::shared_ptr<CVariable>> GetDependentVariables();
	void Clear();
	void Calc();
private:
	std::vector<std::shared_ptr<CVariable>> m_dependentVariables;
	std::pair<std::shared_ptr<CValueHolder>, std::shared_ptr<CValueHolder>> m_arguments;
	std::string m_operation;
};