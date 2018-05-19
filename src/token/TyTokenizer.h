#pragma once

#include "common/TyObject.h"
#include "Token.h"

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <map>

namespace ty
{
//-- ## PUBLIC API ## --//

class TyTokenizerConfig
{
public:
	void add(TokenType tt, std::string match);

	//! Must be called before it is used
	void prioritize_tokens();

protected:
	std::unordered_map<char, std::vector<std::pair<std::string, TokenType>>>	m_tokens;
};

struct TokenException;

class TyTokenizer : public TyTokenizerConfig
{
public:
	explicit TyTokenizer(TyTokenizerConfig cfg)
		: TyTokenizerConfig{ std::move(cfg) }
	{
		prioritize_tokens();
	}

	TyTokenizer()
		: TyTokenizer(make_default_config())
	{}

	// Tokenize the string assuming that it is valid
	// may throw TokenException, if invalid
	TokenList tokenize(std::shared_ptr<std::string> text);
	
	// Creates a copy of 'text' as a shared_ptr 
	// Calls tokenize(shared_ptr<string>)
	TokenList tokenize(std::string text) { return tokenize(std::make_shared<std::string>(text)); }

	// print a helpful debugging message showing where the exception occurred
	void print_exception(std::string const& text, TokenException const&) {}

private:
	TyTokenizerConfig make_default_config();
};

} // namespace ty

