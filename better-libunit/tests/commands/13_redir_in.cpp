#include "commands.hpp"

int	redir_in( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)"echo test > 1.txt", environ, &table, 0);
	run_pipeline(&table);

	init_table((char *)"cat < 1.txt", environ, &table, 0);
	Libunit::Redirect_log();
	if (Libunit::Check_output("test") == 0)
		return (0);
	else
		return (1);
}