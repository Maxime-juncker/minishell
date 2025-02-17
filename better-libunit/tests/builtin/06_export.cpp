#include "builtin.hpp"

int	export_test( void )
{
	const char *expected[]
	{
		"hello",
	};

	t_command_table	table;
	table.env = duplicate_env(environ);
	table.exp = duplicate_env(environ);

	init_table(process_line("export TEST=hello", table.env, NULL), &table, 0);
	run_pipeline(&table);

	Libunit::Redirect_log();

	init_table(process_line("echo $TEST", table.env, NULL), &table, 0);
	run_pipeline(&table);
	if (Libunit::CheckFile("log.txt", expected, 1) == 0)
		return (0);
	else
		return (1);
}
