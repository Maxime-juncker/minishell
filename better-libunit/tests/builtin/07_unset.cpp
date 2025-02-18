#include "builtin.hpp"


int	unset_test( void )
{
	const char *expected[]
	{
		"",
	};

	t_command_table	table;
	table.env = duplicate_env(environ);
	table.exp = duplicate_env(environ);

	// set a env var
	init_table((char *)"export TEST=hello", &table);
	run_pipeline(&table);

	init_table((char *)"unset TEST", &table);

	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::CheckFile("log.txt", expected, 1) == 0)
		return (0);
	else
		return (1);
}
