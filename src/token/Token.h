#pragma once

#include "common/TyObject.h"
#include <memory>
#include <string>
#include <vector>

namespace ty
{

enum class TokenType : uint64_t;

//! A Token is only valid as long as the parent TyTokenizer is alive
class Token : public TyObject<>
{
   TokenType m_type;

   char const* m_pos;

   size_t m_len;

   std::shared_ptr<std::string> m_text;

 public:
   Token(TokenType tt, char const* pos, size_t len, std::shared_ptr<std::string> t)
     : m_type{ tt }
     , m_pos{ pos }
     , m_len{ len }
     , m_text{ std::move(t) }
   {
   }

   TokenType type() const noexcept { return m_type; }

   static char const* as_string(TokenType t);

   bool is(TokenType t) const { return m_type == t; }

   bool operator==(TokenType t) const { return is(m_type); }

   std::string value() const noexcept { return std::string{ m_pos, m_len }; }
};

inline bool operator==(TokenType t1, Token const& t2) { return t2 == t1; }

using TokenList = std::vector<Token>;

} // namespace ty
