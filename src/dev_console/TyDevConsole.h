#pragma once

#include "common/TyConsole.h"
#include <vector>

namespace ty
{
class TokenizeCmd : public TyCommandBase
{
   enum class mode
   {
      from_file,
      from_arg,
      from_stdin
   };

   mode m_mode = mode::from_file;

   std::vector<std::string> m_targets;

 public:
   bool add_option(std::string const& option_name) override
   {
      if (option_name == "from-file")
      {
         m_mode = mode::from_file;
         return true;
      }
      if (option_name == "from-stdin")
      {
         m_mode = mode::from_stdin;
         return true;
      }
      if (option_name == "from-arg")
      {
         m_mode = mode::from_arg;
         return true;
      }
      return false;
   }

   bool add_target(std::string const& target) override
   {
      m_targets.emplace_back(target);
      return true;
   }

   bool execute() const override
   {
      if (m_mode == mode::from_file)
      {
      }

      if (m_mode == mode::from_stdin)
      {
      }

      if (m_mode == mode::from_arg)
      {
         TY_ASSERTF(!m_targets.empty(), "No arguments present to tokenize%c", '\n');
         return execute_from_string(m_targets[0]);
      }
      return false;
   }

   void print_help() const override {}

 private:
   bool execute_from_string(std::string const& arg) const;
};

class TyDevConsole : public TyGenericConsole
{
 public:
   TyDevConsole(TyGenericConsole base)
     : TyGenericConsole{ std::move(base) }
   {
      add_command("tokenize", std::make_unique<TokenizeCmd>());
   }

   void print_help() const override {}
};

class ParseCmd : public TyCommandBase
{
 public:
   bool add_option(std::string const& option_name) override { return false; }

   bool add_target(std::string const& command_name) override { return false; }

   void print_help() const override {}

   bool execute() const override { return false; }
};

inline auto make_dev_console()
{
   TyGenericConsole cs;
   cs.add_command("parse", std::make_unique<ParseCmd>());

   return TyDevConsole{ std::move(cs) };
}
} // namespace ty
