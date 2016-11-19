#include "stdafx.h"
#include "Calculator.h"
#include "Menu.h"
#include "calculator_utils.h"

int main()
{
	CCalculator calculator;
	CMenu menu;
	menu.AddItem("help", "Give information about command", [&menu](CCalculator &, const std::string &)
	{
		menu.ShowInstructions();
	});
	menu.AddItem("exit", "Exit from programm", [&menu](CCalculator &, const std::string &)
	{
		menu.Exit();
	});
	menu.AddItem("var", " <name> : Create new variable", ExecuteVar);
	menu.AddItem("let", " <name> = <ident>|<double number> : Create new variable and set value, or just set value", ExecuteLet);
	menu.AddItem("fn", " <name> = <ident>[+|-|*|/ <ident>]> : Create new function", ExecuteFn);
	menu.AddItem("print", " <name> : Print element value", ExecutePrint);
	menu.AddItem("printvars", " <name> : Print all variables value", ExecutePrintVars);
	menu.AddItem("printfns", " <name> : Print all functions value", ExecutePrintFns);
	menu.Run(calculator);
	return 0;
}

