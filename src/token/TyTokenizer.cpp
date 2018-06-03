#include "TyTokenizer.h"
#include "TokenException.h"
#include "TokenType.h"
#include <algorithm>
#include <cstring>

namespace ty
{

char const* Token::as_string(TokenType t)
{
  switch (t)
  {
    case TokenType::BRACE_OPEN:
      return "brace_open";
    case TokenType::BRACE_CLOSE:
      return "brace_close";
    case TokenType::PAREN_OPEN:
      return "paren_open";
    case TokenType::PAREN_CLOSE:
      return "paren_close";
    case TokenType::ID:
      return "id";
    case TokenType::EQ:
      return "defn";
    case TokenType::DECL:
      return "decl";
    case TokenType::AT:
      return "AT";
    case TokenType::PLUS:
      return "plus";
    case TokenType::MINUS:
      return "minus";
    case TokenType::ARROW:
      return "arrow";
    case TokenType::INT_LITERAL:
      return "int-literal";
    case TokenType::COMMA:
      return "comma";
    case TokenType::EXPORT:
      return "export";
    case TokenType::END_OF_FILE:
      return "eof";
    default:
    case TokenType::UNKNOWN:
      return "unknown";
  }
}

void TyTokenizerConfig::add(TokenType tt, std::string s)
{
  // TY_ASSERTF(s.size(), "Cannot add token with empty matcher lexeme");
  auto& v = m_tokens[s[0]];
  v.emplace_back(std::move(s), tt);
}

void TyTokenizerConfig::prioritize_tokens()
{
  for (auto& v : m_tokens)
  {
    std::sort(v.second.begin(), v.second.end(),
              [](auto const& p1, auto const& p2) { return p1.first.size() > p2.first.size(); });
  }
}

TyTokenizerConfig TyTokenizer::make_default_config()
{
  TyTokenizerConfig cfg;
  cfg.add(TokenType::BRACE_OPEN, "{");
  cfg.add(TokenType::COMMA, ",");
  cfg.add(TokenType::BRACE_CLOSE, "}");
  cfg.add(TokenType::PAREN_OPEN, "(");
  cfg.add(TokenType::PAREN_CLOSE, ")");
  cfg.add(TokenType::LT, "<");
  cfg.add(TokenType::GT, ">");
  cfg.add(TokenType::LEQ, "<=");
  cfg.add(TokenType::GEQ, ">=");
  cfg.add(TokenType::PLUS, "+");
  cfg.add(TokenType::MINUS, "-");
  cfg.add(TokenType::EQ, "=");
  cfg.add(TokenType::DECL, ":");
  cfg.add(TokenType::DOT, ".");
  cfg.add(TokenType::ELLIPSIS, "..");
  cfg.add(TokenType::AT, "@");
  cfg.add(TokenType::SEMICOLON, ";");
  cfg.add(TokenType::ARROW, "->");
  // cfg.add(TokenType::EXPORT, "{");
  // cfg.add(TokenType::RETURN, "{");
  cfg.add(TokenType::INCREMENT, "++");
  cfg.add(TokenType::DECREMENT, "--");
  cfg.add(TokenType::PLUS_EQ, "+=");
  cfg.add(TokenType::MINUS_EQ, "-=");
  cfg.add(TokenType::CHECK_EQ, "==");

  return cfg;
}

TokenList TyTokenizer::tokenize(std::shared_ptr<std::string> text)
{
  auto cstr_begin = text->c_str();
  auto cstr_end = cstr_begin + text->size();

  TokenList out_list;

  auto const add_token = [&out_list, t = text](TokenType tt, auto& p, size_t n) {
    out_list.emplace_back(tt, p, n, std::move(t));
    p += n;
  };

  for (auto p = cstr_begin; p < cstr_end;)
  {
    while (::isspace(*p) && p < cstr_end)
      p++;
    if (p >= cstr_end)
      break;

    auto const it = m_tokens.find(p[0]);

    if (it != m_tokens.end())
    {
      bool found = false;
      for (auto const& l : it->second)
      {
        if (0 == ::strncmp(l.first.c_str(), p, l.first.size()))
        {
          add_token(l.second, p, l.first.size());
          found = true;
          break;
        }
      }
      TY_ASSERTF(found, "Failed to match token at '%s'", p);
      continue;
    }

    if (::isalpha(*p))
    {
      size_t n = 0;
      for (n = 0; ::isalpha(p[n]) || p[n] == '_'; ++n)
      {
      }
      add_token(TokenType::ID, p, n);
      continue;
    }

    if (::isdigit(*p))
    {
      size_t n = 0;
      for (n = 0; ::isdigit(p[n]); ++n)
      {
      }
      add_token(TokenType::INT_LITERAL, p, n);
      continue;
    }

    if (*p == '/' && p[1] == '/')
    {
      while (*p != '\n' && p < cstr_end)
        p++;
      continue;
    }

    throw TokenException(p, text);
  }
  out_list.emplace_back(TokenType::END_OF_FILE, "", 0, nullptr);
  return out_list;
}
}
