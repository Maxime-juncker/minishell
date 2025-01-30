#include "commands.hpp"

int	expanded_var( void )
{
	t_command_table	table;

	init_table((char *)"echo $DESKTOP_SESSION", environ, &table);
	Libunit::Redirect_log();
	run_pipeline(table);
	if (Libunit::Check_output("ubuntu\n") == 0)
		return (0);
	else
		return (1);
}