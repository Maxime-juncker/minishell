#include "builtin.hpp"

int	env_test( void )
{
	t_command_table table;
	table.env = duplicate_env(environ);
	table.exp = duplicate_env(environ);;

	Libunit::Redirect_log();
	env(table);
	if (Libunit::Check_output("ABCDEF") != 0)
		return (0);
	else
		return (1);
}