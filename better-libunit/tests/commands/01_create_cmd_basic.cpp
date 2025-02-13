#include "commands.hpp"

int	create_cmd( void )
{
	t_command_table	table;

	init_table((char *)"ls -l", &table, 0);
	if (ft_strncmp(table.commands[0].args[0], "ls", 2) != 0
		|| ft_strncmp(table.commands[0].args[1], "-l", 2) != 0)
		return (1);
	if (table.n_commands > 1)
		return (1);
	return (0);
}