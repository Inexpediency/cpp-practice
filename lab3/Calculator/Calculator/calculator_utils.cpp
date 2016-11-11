#include "stdafx.h"
#include "calculator_utils.h"

const std::string identPattern = "[A-Za-z](\\w)*";
const std::string doubleNumberPattern = "\\d+(\\.\\d+)?";
const std::string spacesPattern = "( )*";
const std::string signPattern = "(\\+|\\*|/|-)";
const std::string letPattern = spacesPattern + identPattern + spacesPattern + "=" + spacesPattern + "((" + identPattern + ")|(" + doubleNumberPattern + "))" + spacesPattern;
const std::string fnPattern = spacesPattern + identPattern + spacesPattern + "=" + spacesPattern + identPattern + spacesPattern + "(" + signPattern + spacesPattern + identPattern + spacesPattern + ")?";

std::vector<std::string> GetIdents(const std::string & string)
{
	std::smatch matchResult;
	std::vector<std::string> result;
	std::string str(string);
	while (std::regex_search(str, matchResult, std::regex(identPattern)))
	{
		std::string ident = matchResult[0];
		str.erase(str.find(ident), ident.size());
		result.insert(result.cend(), ident);
	}
	return result;
}

std::vector<double> GetNumbers(const std::string & string)
{
	std::smatch matchResult;
	std::vector<double> result;
	std::string str(string);
	while (std::regex_search(str, matchResult, std::regex(doubleNumberPattern)))
	{
		std::string number = matchResult[0];
		str.erase(str.find(number), number.size());
		result.insert(result.cend(), stod(number));
	}
	return result;
}

void ExecuteVar(CCalculator & calculator, const std::string & params)
{
	if (!std::regex_match(params, std::regex(spacesPattern + identPattern + spacesPattern)))
	{
		std::cout << "Error:: not valid arguments" << std::endl;
		return;
	}
	std::string ident = GetIdents(params)[0];
	try
	{
		calculator.AddVariable(ident);
	}
	catch (std::logic_error & exeption)
	{
		std::cout << "Error::" + std::string(exeption.what()) << std::endl;
	}
}

template <class T>
void AddValue(CCalculator & calculator, const std::string & name, const T & value)
{
	try
	{
		calculator.AddVariable(name, value);
	} 
	catch (std::invalid_argument & exeption)
	{
		std::cout << "Error::" + std::string(exeption.what()) << std::endl;
	}
	catch (std::logic_error &)
	{
		try
		{
			calculator.SetVariableValue(name, value);
		}
		catch (std::invalid_argument & exeption)
		{
			std::cout << "Error::" + std::string(exeption.what()) << std::endl;
		}
	}
}

void ExecuteLet(CCalculator & calculator, const std::string & params)
{
	if (!std::regex_match(params, std::regex(letPattern)))
	{
		std::cout << "Error:: not valid arguments" << std::endl;
		return;
	}
	std::vector<std::string> idents = GetIdents(params);
	std::vector<double> numbers = GetNumbers(params);

	if (idents.size() == 2)
	{
		AddValue(calculator, idents[0], idents[1]);
	}
	else
	{
		AddValue(calculator, idents[0], numbers[0]);
	}
}

std::string GetSign(const std::string & str)
{
	std::smatch result;
	std::regex_search(str, result, std::regex(signPattern));
	return *result.cbegin();
}

void ExecuteFn(CCalculator & calculator, const std::string & params)
{
	if (!std::regex_match(params, std::regex(fnPattern)))
	{
		std::cout << "Error:: not valid arguments" << std::endl;
		return;
	}
	std::vector<std::string> idents = GetIdents(params);
	try
	{
		if (idents.size() == 2)
		{
			calculator.AddFunction(idents[0], idents[1]);
		}
		else
		{
			calculator.AddFunction(idents[0], idents[1], idents[2], GetSign(params));
		}
	}
	catch (std::logic_error & exeption)
	{
		std::cout << "Error::" + std::string(exeption.what()) << std::endl;
	}
}

void ExecutePrint(const CCalculator & calculator, const std::string & params)
{
	if (!std::regex_match(params, std::regex(spacesPattern + identPattern + spacesPattern)))
	{
		std::cout << "Error:: not valid arguments" << std::endl;
		return;
	}
	try
	{
		calculator.PrintElement(std::cout, GetIdents(params)[0]);
	}
	catch (std::logic_error & exeption)
	{
		std::cout << "Error::" + std::string(exeption.what()) << std::endl;
	}
}

void ExecutePrintFns(const CCalculator & calculator, const std::string & params)
{
	calculator.PrintFunctions(std::cout);
}

void ExecutePrintVars(const CCalculator & calculator, const std::string & params)
{
	calculator.PrintVariables(std::cout);
}