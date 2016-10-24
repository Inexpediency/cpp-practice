
#pragma once

#include <iterator>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <boost/range/algorithm/find_if.hpp>
#include <functional>
#include "Car.h"

class CCarMenu
{
public:
	typedef std::function<void(CCar &, const std::string &)> Command;
	void AddItem(
		const std::string & shortcut,
		const std::string & description,
		const Command & command)
	{
		m_items.emplace_back(shortcut, description, command);
	}

	void Run(CCar & car)
	{
		ShowInstructions();

		std::string command;
		while ((std::cout << ">") && 
			getline(std::cin, command) && 
			ExecuteCommand(car, command))
		{}
	}

	void ShowInstructions() const
	{
		std::cout << "Commands list:\n";
		for (auto & item : m_items)
		{
			std::cout << "'" << item.shortcut << "': " << item.description << "\n";
		}
	}

	void Exit()
	{
		m_exit = true;
	}

private:
	bool ExecuteCommand(CCar & car, const std::string & command)
	{
		m_exit = false;
		auto it = boost::find_if(m_items, [&](const Item & item) {
			return command.find(item.shortcut) != std::string::npos;
		});
		if (it != m_items.end())
		{
			std::string arguments = command.substr(it->shortcut.length(), command.length() - it->shortcut.length());
			it->command(car, arguments);
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