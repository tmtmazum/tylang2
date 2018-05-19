#pragma once

namespace ty
{
	//enum class TokenType
	//{
	//	ID,
	//	INT_LITERAL,
	//	PAREN_OPEN,
	//	PAREN_CLOSE,
	//	BRACE_OPEN,
	//	BRACE_CLOSE,
	//	END_OF_FILE
	//};

	enum class TokenType : uint64_t
	{ 
		UNKNOWN, 

		// Single-character tokens
		BRACE_OPEN = 100,  
		COMMA, 
		BRACE_CLOSE, 
		PAREN_OPEN, 
		PAREN_CLOSE, 
		LT,
		GT,
		LEQ,
		GEQ,
		PLUS, 
		MINUS, 
		EQ, 
		DECL, 
		DOT,
		ELLIPSIS,
		AT, 
		SEMICOLON,

		// Multi-character tokens
		ARROW = 200, 
		EXPORT, 
		RETURN, 
		INCREMENT,
		DECREMENT,
		PLUS_EQ,
		MINUS_EQ,
		CHECK_EQ,
	

		// Special tokens
		ID = 300, 
		INT_LITERAL, 
		END_OF_FILE 
	};

}