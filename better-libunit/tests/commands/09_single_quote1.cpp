#include "commands.hpp"

int	single_quote_basic( void )
{
	t_command_table	table;
	table.env = environ;

	init_table(process_line("echo \'$HOME\'"), environ, &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);
	if (Libunit::Check_output("$HOME\n") == 0)
		return (0);
	else
		return (1);
}