#include "builtin.hpp"

int	env_test( void )
{
	t_command_table table;
	t_command		cmd;
	table.env = duplicate_env(environ);
	table.exp = duplicate_env(environ);;
	cmd.n_args = 0;

	Libunit::Redirect_log();
	env(table, cmd);
	if (Libunit::Check_output("ABCDEF") != 0)
		return (0);
	else
		return (1);
}