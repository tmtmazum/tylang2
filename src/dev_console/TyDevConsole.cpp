#include "TyDevConsole.h"
#include "token/TyTokenizer.h"
#include <string>
#include <iostream>

namespace ty
{

bool TokenizeCmd::execute_from_string(std::string const& arg) const
{
   // TY_STDOUT("Tokenizing string '%s'", arg.c_str());
   // TY_STDOUT("-----------------------------------%c", '-');
   TyTokenizer tk;
   auto tl = tk.tokenize(arg);
   for (auto const& t : tl)
   {
      TY_STDOUT("<token:%s '%s'> ", Token::as_string(t.type()), t.value().c_str());
   }
   // TY_STDOUT("-----------------------------------%c", '-');
   return true;
}

bool TokenizeCmd::execute_from_stdin() const
{
  while(1)
  {
    std::string text;
    std::getline(std::cin, text);
    execute_from_string(text);
  }
}

} // namespace ty
