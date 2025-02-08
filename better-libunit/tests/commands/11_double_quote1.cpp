#include "commands.hpp"

int	double_quote_basic( void )
{
	t_command_table	table;
	table.env = environ;

	init_table(process_line("echo \"$DESKTOP_SESSION\""), environ, &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);
	if (Libunit::Check_output("ubuntu\n") == 0)
		return (0);
	else
		return (1);
}