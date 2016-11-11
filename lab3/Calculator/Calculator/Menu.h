#pragma once

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <boost/range/algorithm/find_if.hpp>
#include <functional>
#include "Calculator.h"
#include <regex>

class CMenu
{
public:
	typedef std::function<void(CCalculator & calculator, const std::string & arguments)> Command;
	void AddItem(
		const std::string & shortcut,
		const std::string & description,
		const Command & command)
	{
		m_items.emplace_back(shortcut, description, command);
	}

	void Run(CCalculator & calculator)
	{
		ShowInstructions();

		std::string command;
		while ((std::cout << ">")
			&& getline(std::cin, command)
			&& ExecuteCommand(command, calculator))
		{
		}
	}

	void ShowInstructions()const
	{
		std::cout << "Commands list:\n";
		for (auto & item : m_items)
		{
			std::cout << "  " << item.shortcut << ": " << item.description << "\n";
		}
	}

	void Exit()
	{
		m_exit = true;
	}

private:
	bool ExecuteCommand(const std::string & command, CCalculator & calculator)
	{
		m_exit = false;
		auto it = boost::find_if(m_items, [&](const Item & item) {
			return std::regex_match(command, std::regex("( )*" +  item.shortcut + "((\\s(.)*)|$)"));
		});
		std::cout << it->shortcut << std::endl;
		if (it != m_items.end())
		{
			std::string arguments = command.substr(it->shortcut.length(), command.length() - it->shortcut.length());
			it->command(calculator, arguments);
		}
		else
		{
			std::cout << "Unknown command\n";
		}
		return !m_exit;
	}

	struct Item
	{
		Item(const std::string & shortcut, const std::string & description, const Command & command)
			: shortcut(shortcut)
			, description(description)
			, command(command)
		{}

		std::string shortcut;
		std::string description;
		Command command;
	};
	std::vector<Item> m_items;
	bool m_exit = false;
};