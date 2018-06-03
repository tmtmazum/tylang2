#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace ty
{

class Expr;

class SymbolMap
{
private:
	std::unordered_map<std::string, std::unique_ptr<Expr>>		m_map;
};

}
