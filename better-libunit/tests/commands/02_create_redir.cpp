#include "commands.hpp"

int	create_redir( void )
{
	t_command_table	table;

	init_table((char *)"ls -l > out", &table);
	if (table.commands[0].fd_out != STDOUT_FILENO)
		return (0);
	else
		return (1);
}