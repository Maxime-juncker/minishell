#include "commands.hpp"

int	pipe_after_redir( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)"echo test | wc -c > log.txt | wc -l", environ, &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);
	if (Libunit::Check_output("1\n") == 0)
		return (0);
	else
		return (1);
}