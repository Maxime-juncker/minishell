#include "commands.hpp"

int	redir_after_pipe( void )
{
	t_command_table	table;

	init_table((char *)"echo test | wc -c > log.txt", environ, &table, 0);
	run_pipeline(&table);
	if (Libunit::Check_output("5\n") == 0)
		return (0);
	else
		return (1);
}