#pragma once

#include "TyObject.h"
#include <memory>
#include <string>
#include <unordered_map>

namespace ty
{
	/* Free Functions*/

	std::unique_ptr<std::string> extract_as_option(std::string const& option_name)
	{
		if (option_name.empty()) return nullptr;
		if (option_name[0] == '/')
		{
			return std::make_unique<std::string>(option_name.substr(1));
		}

		if (option_name.size() >= 2 && option_name[0] == '-' && option_name[1] == '-')
		{
			return std::make_unique<std::string>(option_name.substr(2));
		}
		return nullptr;
	}

	class TyCommandBase : public TyVirtual<TyObject<>>
	{
	public:
		virtual bool add_option(std::string const& option_name) = 0;

		virtual bool add_target(std::string const& command_name) = 0;

		virtual void print_help() const = 0;
	};
	
	class TyConsoleBase : public TyVirtual<TyObject<>>
	{
	public:
		static constexpr int minimum_args() { return 2; }

		virtual TyCommandBase* find_command(std::string cmd) const = 0;

		virtual void print_help() const = 0;
	};

	class TyGenericConsole : public TyConsoleBase
	{
		std::unordered_map<std::string, std::unique_ptr<TyCommandBase>> m_commands;

	public:
		void add_command(std::string name, std::unique_ptr<TyCommandBase> cmd)
		{
			m_commands.emplace(std::move(name), std::move(cmd));
		}

		TyCommandBase* find_command(std::string cmd) const override
		{
			auto it = m_commands.find(cmd);
			return it == m_commands.end() ? nullptr : it->second.get();
		}
		void print_help() const override {}
	};

} // namespace ty
