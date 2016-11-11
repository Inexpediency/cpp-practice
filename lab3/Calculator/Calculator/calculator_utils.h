#pragma once
#include <string>
#include <vector>
#include "Calculator.h"

std::vector<std::string> GetIdents(const std::string & str);
std::vector<double> GetNumbers(const std::string & str);
void ExecuteVar(CCalculator & calculator, const std::string & params);
void ExecuteLet(CCalculator & calculator, const std::string & params);
void ExecuteFn(CCalculator & calculator, const std::string & params);
void ExecutePrint(const CCalculator & calculator, const std::string & params);
void ExecutePrintFns(const CCalculator & calculator, const std::string & params);
void ExecutePrintVars(const CCalculator & calculator, const std::string & params);