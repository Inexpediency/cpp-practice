#include "stdafx.h"
#include "print_utils.h"
#include "CValueHolder.h"
#include "Function.h"
#include "Variable.h"


void PrintElement(std::ostream & output, const CCalculator & calc, const std::string & name)
{
	auto element = calc.GetElement(name);
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

void PrintFunctions(std::ostream & output, const CCalculator & calc)
{
	output << std::fixed;
	output << std::setprecision(2);
	auto fns = calc.GetFuncs();
	for (auto element : fns)
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

void PrintVariables(std::ostream & output, const CCalculator & calc)
{
	output << std::fixed;
	output << std::setprecision(2);
	auto vars = calc.GetVars();
	for (auto element : vars)
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