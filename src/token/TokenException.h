#pragma once

#include "common/TyObject.h"
#include <memory>
#include <string>

namespace ty
{

struct TokenException : public TyException
{
   char const* m_pos;

   std::shared_ptr<std::string> m_text;

   TokenException()
     : TyException{ "TokenException" }
   {
   }

   TokenException(char const* pos, std::shared_ptr<std::string> text)
     : TyException{ "TokenException" }
     , m_pos{ pos }
     , m_text{ std::move(text) }
   {
   }

   void log_to_stdout() const
   {
      for (auto const& c : *m_text)
      {
         auto const is_error = &c == m_pos;

         fputc(c, stdout);
         if (is_error)
         {
            fprintf(stdout, "`Unrecognized token encountered here`");
         }
      }
      fputc('\n', stdout);
   }
};
}
