#pragma once
#include <map>
#include <string>
#include <functional>
#include <memory>

const std::map<std::string, std::function<double(double, double)>> OPERATIONS = {
	{ "+", [](double a, double b) -> double { return a + b; } },
	{ "-", [](double a, double b) -> double { return a - b; } },
	{ "*", [](double a, double b) -> double { return a * b; } },
	{ "/", [](double a, double b) -> double { return a / b; } },
};