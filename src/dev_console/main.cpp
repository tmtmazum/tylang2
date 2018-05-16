#include "TyDevConsole.h"


int main(int argc, char** argv) try
{
	using namespace ty;

	auto const console = make_dev_console();

	TY_ASSERTF(argc >= console.minimum_args(), "argc: %d", argc);

	auto cmd = console.find_command(argv[1]);

	if (!cmd)
	{
		TY_STDERR("Unrecognized command '%s'", argv[1]);
		return EXIT_FAILURE;
	}

	for(int i = 2; i < argc; ++i)
	{
		if(auto option_name = ty::extract_as_option(argv[i]))
		{
			if (!cmd->add_option(*option_name))
			{
				TY_STDERR("Invalid option '%s' for command '%s'", option_name->c_str(), argv[1]);
				return EXIT_FAILURE;
			}
			continue;
		}

		if (!cmd->add_target(argv[i]))
		{
			TY_STDERR("Invalid target '%s' for command '%s'", argv[i], argv[1]);
			return EXIT_FAILURE;
		}
	}	
	return EXIT_SUCCESS;
} 
catch(...)
{
	TY_STDERR("Unknown exception occurred.");
	return EXIT_FAILURE;
}
