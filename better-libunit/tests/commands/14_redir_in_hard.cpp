#include "commands.hpp"

int	redir_in_hard( void )
{
	t_command_table	table;
	table.env = duplicate_env(environ);
	table.exp = duplicate_env(environ);;
	int	code;

	init_table(process_line("< 1.txt cat", table.env, &code), &table);
	if (table.n_commands == 1)
		return (0);
	else
		return (1);
}