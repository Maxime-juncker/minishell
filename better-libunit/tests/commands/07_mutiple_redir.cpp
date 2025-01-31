#include "commands.hpp"
#include <fcntl.h>

int	mutiple_redir( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)"echo test > 1 > 2 > 3 > 4", environ, &table, 0);
	run_pipeline(&table);
	if (open("4", O_RDONLY, 0777) != -1)
		return (0);
	else
		return (1);
}