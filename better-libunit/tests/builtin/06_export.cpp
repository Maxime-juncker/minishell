#include "builtin.hpp"

static char*	get_last_env_var(t_command_table table)
{
	int	i = 0;

	while (table.env[i] != NULL)
	{
		i++;
	}
	return (table.env[i - 1]);
}

int	export_test( void )
{
	t_command_table	table;

	init_table((char *)"export TEST=hello", &table, 0);
	table.env = environ;


	run_pipeline(&table);
	std::string last = get_last_env_var(table);
	if (last == "TEST=hello")
		return (0);
	else
		return (1);
}
