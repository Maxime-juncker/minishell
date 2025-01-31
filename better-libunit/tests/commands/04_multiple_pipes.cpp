#include "commands.hpp"

int	create_mulitple_pipes( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)"sleep 1 | echo test | wc -c | wc -l", environ, &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);
	if (Libunit::Check_output("1\n") == 0)
		return (0);
	else
		return (1);
}