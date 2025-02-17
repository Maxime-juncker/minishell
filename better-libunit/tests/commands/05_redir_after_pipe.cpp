#include "commands.hpp"

int	redir_after_pipe( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)"echo test | wc -c > log.txt", &table);
	run_pipeline(&table);
	if (Libunit::Check_output("5\n") == 0)
		return (0);
	else
		return (1);
}