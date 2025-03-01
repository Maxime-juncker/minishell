#include "commands.hpp"


int	ls_basic( void )
{
	t_command_table table;
	table.env = duplicate_env(environ);
	table.exp = duplicate_env(environ);;

	int code;
	init_table(process_line("ls", table.env, &code), &table);

	Libunit::Redirect_log();
	run_pipeline(&table, NULL);
	if (Libunit::Check_output("\n") != 0)
		return (0);
	else
		return (1);
}
