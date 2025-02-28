#include "commands.hpp"

int	redir_after_pipe( void )
{
	t_command_table	table;
	table.env = duplicate_env(environ);
	table.exp = duplicate_env(environ);
	int code;

	init_table(process_line("echo test | wc -c > log.txt", table.env, &code), &table);
	run_pipeline(&table, NULL);
	if (Libunit::Check_output("5\n") == 0)
		return (0);
	else
		return (1);
}