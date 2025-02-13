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

int	unset_test( void )
{
	t_command_table	table;
	table.env = environ;

	std::string before = get_last_env_var(table);

	// set a env var
	init_table((char *)"export TEST=hello", &table, 0);
	run_pipeline(&table);

	init_table((char *)"unset TEST=hello", &table, 0);
	run_pipeline(&table);

	std::string last = get_last_env_var(table);
	if (last == before)
		return (0);
	else
		return (1);
}
