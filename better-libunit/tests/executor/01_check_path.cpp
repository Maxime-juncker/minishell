#include "executor.hpp"
#include <iostream>
int	test_path( void )
{
	t_command_table	table;
	table.env = environ;
	init_table((char *)"ls -l", table.env, &table, 0);
	std::string path = table.commands[0].path;
	if (path.compare("/usr/bin/ls") == 0)
		return (0);
	else
		return (1);
}