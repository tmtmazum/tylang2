#include "token/TyTokenizer.h"
#include "token/TokenType.h"
#include "token/TokenException.h"
#include <gtest/gtest.h>

using namespace ty;

TEST(sanity, sanity)
{
	EXPECT_EQ(1, 1);
}

TEST(tokenizer, empty)
try
{
	TyTokenizer t{ TyTokenizerConfig{} };
	auto list = t.tokenize("");
	ASSERT_EQ(1, list.size());
	ASSERT_EQ(TokenType::END_OF_FILE, list[0]);
}
catch (TokenException const& e)
{
	e.log_to_stdout();
	ASSERT_FALSE(true);
}

TEST(tokenizer, ambiguous_symbols)
try
{
	TyTokenizerConfig cfg;
	cfg.add(TokenType::MINUS, "-");
	cfg.add(TokenType::DECREMENT, "--");
	cfg.add(TokenType::MINUS_EQ, "-=");
	cfg.add(TokenType::ARROW, "->");
	cfg.add(TokenType::EQ, "=");
	cfg.add(TokenType::CHECK_EQ, "==");

	TyTokenizer t{ std::move(cfg) };
	auto list = t.tokenize("a -= b - --c->data--");
	int i = 0;
	ASSERT_EQ(TokenType::ID, list[i++]);
	ASSERT_EQ(TokenType::MINUS_EQ, list[i++]);
	ASSERT_EQ(TokenType::ID, list[i++]);
	ASSERT_EQ(TokenType::MINUS, list[i++]);
	ASSERT_EQ(TokenType::DECREMENT, list[i++]);
	ASSERT_EQ(TokenType::ID, list[i++]);
	ASSERT_EQ(TokenType::ARROW, list[i++]);
	ASSERT_EQ(TokenType::ID, list[i++]);
	ASSERT_EQ(TokenType::DECREMENT, list[i++]);
	ASSERT_EQ(TokenType::END_OF_FILE, list[i++]);
}
catch (TokenException const& e)
{
	e.log_to_stdout();
	ASSERT_FALSE(true);
}

TEST(tokenizer, empty_ws)
try
{
	TyTokenizer t;
	auto list = t.tokenize(R"(  
	)");
	ASSERT_EQ(1, list.size());
	ASSERT_EQ(TokenType::END_OF_FILE, list[0]);
}
catch (TokenException const& e)
{
	e.log_to_stdout();
	ASSERT_FALSE(true);
}


TEST(tokenizer, int_literal)
try
{
	TyTokenizer t;
	auto list = t.tokenize(R"(12512)");
	ASSERT_EQ(2, list.size());
	ASSERT_EQ(TokenType::INT_LITERAL, list[0]);
	ASSERT_EQ(TokenType::END_OF_FILE, list[1]);
}
catch (TokenException const& e)
{
	e.log_to_stdout();
	ASSERT_FALSE(true);
}



TEST(tokenizer, int_literal_2)
try
{
	TyTokenizer t;
	auto list = t.tokenize(R"(125 12)");
	ASSERT_EQ(3, list.size());
	ASSERT_EQ(TokenType::INT_LITERAL, list[0]);
	ASSERT_EQ(TokenType::INT_LITERAL, list[1]);
	ASSERT_EQ(TokenType::END_OF_FILE, list[2]);
}
catch (TokenException const& e)
{
	e.log_to_stdout();
	ASSERT_FALSE(true);
}


TEST(tokenizer, id_underscore)
try
{
	TyTokenizer t;
	auto list = t.tokenize(R"(Hello_my_name)");
	ASSERT_EQ(2, list.size());
	ASSERT_EQ(TokenType::END_OF_FILE, list.back());
	ASSERT_EQ(TokenType::ID, list[0]);
	ASSERT_STREQ("Hello_my_name", list[0].value().c_str());
}
catch (TokenException const& e)
{
	e.log_to_stdout();
	ASSERT_FALSE(true);
}


TEST(tokenizer, id2)
try
{
	TyTokenizer t;
	auto list = t.tokenize(R"(Hello_my_name is_)");
	ASSERT_EQ(3, list.size());
	ASSERT_EQ(TokenType::END_OF_FILE, list.back());
	ASSERT_EQ(TokenType::ID, list[0]);
	ASSERT_EQ(TokenType::ID, list[1]);
}
catch (TokenException const& e)
{
	e.log_to_stdout();
	ASSERT_FALSE(true);
}


TEST(tokenizer, words_and_numbers)
try
{
	TyTokenizer t;
	auto list = t.tokenize(R"(The quick brown fox jumped over 112 ducks)");
	ASSERT_EQ(9, list.size());
	ASSERT_EQ(TokenType::END_OF_FILE, list.back());
	ASSERT_EQ(TokenType::ID, list[1]);
	ASSERT_EQ(TokenType::ID, list[list.size()-2]);
	ASSERT_EQ(TokenType::INT_LITERAL, list[list.size()-3]);
}
catch (TokenException const& e)
{
	e.log_to_stdout();
	ASSERT_FALSE(true);
}


TEST(tokenizer, composite0)
try
{
	TyTokenizer t;
	auto list = t.tokenize(R"(foo = @(a, b) { c = a + b; return c; })");
	ASSERT_EQ(TokenType::END_OF_FILE, list.back());
	int i = 0;
	ASSERT_EQ(TokenType::ID, list.at(i++));
	ASSERT_EQ(TokenType::EQ, list.at(i++));
	ASSERT_EQ(TokenType::AT, list.at(i++));
	ASSERT_EQ(TokenType::PAREN_OPEN, list.at(i++));
	ASSERT_EQ(TokenType::ID, list.at(i++));
	ASSERT_EQ(TokenType::COMMA, list.at(i++));
	ASSERT_EQ(TokenType::ID, list.at(i++));
	ASSERT_EQ(TokenType::PAREN_CLOSE, list.at(i++));
	ASSERT_EQ(TokenType::BRACE_OPEN, list.at(i++));
	ASSERT_EQ(TokenType::ID, list.at(i++));
	ASSERT_EQ(TokenType::EQ, list.at(i++));
	ASSERT_EQ(TokenType::ID, list.at(i++));
	ASSERT_EQ(TokenType::PLUS, list.at(i++));
	ASSERT_EQ(TokenType::ID, list.at(i++));
	ASSERT_EQ(TokenType::SEMICOLON, list.at(i++));
	ASSERT_EQ(TokenType::ID, list.at(i++));
	ASSERT_EQ(TokenType::ID, list.at(i++));
	ASSERT_EQ(TokenType::SEMICOLON, list.at(i++));
	ASSERT_EQ(TokenType::BRACE_CLOSE, list.at(i++));
	ASSERT_EQ(TokenType::END_OF_FILE, list.at(i++));
	ASSERT_EQ(i, list.size());
}
catch (TokenException const& e)
{
	e.log_to_stdout();
	ASSERT_FALSE(true);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	auto a = RUN_ALL_TESTS();
	__debugbreak();
	return a;
}
