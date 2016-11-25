#pragma once

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <boost/range/algorithm/find_if.hpp>
#include <functional>

class CMenu
{
public:
	typedef std::function<void(const std::string &)> Command;
	void AddItem(
		const std::string & shortcut,
		const std::string & description,
		const Command & command)
	{
		m_items.emplace_back(shortcut, description, command);
	}

	void Run()
	{
		ShowInstructions();

		std::string command;
		while ((std::cout << ">")
			&& getline(std::cin, command)
			&& ExecuteCommand(command))
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
	bool ExecuteCommand(const std::string & command)
	{
		m_exit = false;
		size_t delimetrPos = command.find(":");
		delimetrPos = delimetrPos == std::string::npos ? command.size() : delimetrPos;
		auto it = boost::find_if(m_items, [&](const Item & item) {
			return item.shortcut == command.substr(0, delimetrPos);
		});
		if (it != m_items.end())
		{
			it->command(command.substr(delimetrPos, command.size() - delimetrPos));
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
