#include "commands.hpp"
#include <fcntl.h>

int	mutiple_redir( void )
{
	t_command_table	table;
	table.env = duplicate_env(environ);
	table.exp = duplicate_env(environ);
	int code;

	init_table(process_line("echo test > 1 > 2 > 3 > 4", table.env, &code), &table);
	run_pipeline(&table);
	if (open("4", O_RDONLY, 0777) != -1)
		return (0);
	else
		return (1);
}