#pragma once

#include "token/Token.h"

namespace ty
{

class TyParserConfig
{

};

struct ParseException;

class TyParser : public TyParserConfig
{
public:
	explicit TyParser(TyParserConfig cfg)
		: TyParserConfig{}
	{
	}

	TyParser()
		: TyParser(make_default_config())
	{}

	// print a helpful debugging message showing where the exception occurred
	void print_exception(std::string const& text, ParseException const&) {}

private:
	TyParserConfig make_default_config();
};

} // namespace ty

