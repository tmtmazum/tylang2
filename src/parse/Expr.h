#pragma once

class Expr
{
	//! Returns if this expression can be evaluated at compile-time 
	virtual bool can_ceval() const noexcept;

	//! Returns list of references to dependant expressions
	// e.g. For '$Assert($IsDefined(abc))':
	//	FnCall{ IdExpr'$Assert' FnCall{ IdExpr'abc' } }
	//	The above expression has a dependency on the symbol $Assert
	//	The symbol-expression $Assert in-turn as a dependency on expression 'abc'
	virtual std::vector<Expr*>	depends() const noexcept {};
};

class NumExpr
{
	bool can_ceval() const noexcept override { return true; }

	std::vector<Expr*>	depends() const noexcept override {};
};

class IdExpr : public Expr
{
	bool can_ceval() const noexcept override { return true; }

	std::vector<Expr*>	depends() const noexcept override {};
};