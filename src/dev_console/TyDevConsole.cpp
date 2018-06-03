#include "TyDevConsole.h"
#include "token/TyTokenizer.h"

namespace ty
{

bool TokenizeCmd::execute_from_string(std::string const& arg) const
{
  TY_STDOUT("Tokenizing string '%s'", arg.c_str());
  TY_STDOUT("-----------------------------------%c", '-');
  TyTokenizer tk;
  auto tl = tk.tokenize(arg);
  for (auto const& t : tl)
  {
    TY_STDOUT("<token:%s '%s'> ", Token::as_string(t.type()), t.value().c_str());
  }
  TY_STDOUT("-----------------------------------%c", '-');
  return true;
}

} // namespace ty
