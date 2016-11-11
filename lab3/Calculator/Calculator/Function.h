#pragma once
#include <map>
#include <memory>
#include <vector>
#include <string>
#include "Valuabal.h"

class CVariable;

class CFunction : public Valuabal
{
public:
	CFunction() = delete;
	CFunction(const std::vector<std::shared_ptr<CVariable>> & dependentVariables, std::shared_ptr<Valuabal> argument1, std::shared_ptr<Valuabal> argument2, const std::string & operation);
	std::vector<std::shared_ptr<CVariable>> GetDependentVariables();
	void Calc();
private:
	std::vector<std::shared_ptr<CVariable>> m_dependentVariables;
	std::pair<std::shared_ptr<Valuabal>, std::shared_ptr<Valuabal>> m_arguments;
	std::string m_operation;
};