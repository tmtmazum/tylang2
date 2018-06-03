#pragma once

#include "Expr.h"
#include "SymbolMap.h"
#include <vector>
#include <memory>

namespace ty
{

class EvalScope : public Expr
{
public:
	std::vector<std::unique_ptr<Expr>>		m_expr_list;

	SymbolMap								m_symbols;

	EvalScope*								m_parent_scope;
};

class FnScope : public EvalScope
{
	std::vector<std::string>				m_args;
};

class TranslationScope : public EvalScope
{
	//! List of symbols specified as being exported (available outside the TLU)
	std::vector<std::string>				m_export_list;

	//! List of symbols specified as being imported within th program
	std::vector<std::string>				m_import_list;

	//! List of symbol-definitions generated implicitly by the compiler before every program
	std::vector<std::string>				m_intrinsic_list;
};

} // namespace ty

