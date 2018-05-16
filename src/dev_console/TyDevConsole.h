#pragma once

#include "common/TyConsole.h"

namespace ty
{
	class TyDevConsole : public TyGenericConsole
	{
	public:
		TyDevConsole(TyGenericConsole base)
			: TyGenericConsole{ std::move(base) }
		{}

		void print_help() const override
		{

		}
	};

	class ParseCmd : public TyCommandBase
	{
	public:
		bool add_option(std::string const& option_name) override
		{
			return false;
		}

		bool add_target(std::string const& command_name) override
		{
			return false;
		}

		void print_help() const override {}
	};

	auto make_dev_console()
	{
		TyGenericConsole cs;
		cs.add_command("parse", std::make_unique<ParseCmd>());

		return TyDevConsole{ std::move(cs) };
	}
}