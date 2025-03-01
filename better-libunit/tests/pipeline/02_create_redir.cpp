#include "commands.hpp"

int	create_redir( void )
{
	t_command_table	table;
	table.env = duplicate_env(environ);
	table.exp = duplicate_env(environ);
	int code;

	init_table(process_line("ls -l > out", table.env, &code), &table);
	if (table.commands[0].fd_out != STDOUT_FILENO)
		return (0);
	else
		return (1);
}