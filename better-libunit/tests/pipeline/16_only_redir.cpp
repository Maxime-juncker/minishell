#include "commands.hpp"

int	redir_in_alone( void )
{
	t_command_table	table;
	table.env = duplicate_env(environ);
	table.exp = duplicate_env(environ);;
	int	code;

	init_table(process_line("< 1.txt", table.env, &code), &table);
	run_pipeline(&table, NULL);
	if (table.n_commands == 0)
		return (0);
	else
		return (1);
}

int	redir_out_alone( void )
{
	t_command_table	table;
	table.env = duplicate_env(environ);
	table.exp = duplicate_env(environ);;
	int	code;

	init_table(process_line("> 1.txt", table.env, &code), &table);
	run_pipeline(&table, NULL);
	if (table.n_commands == 0)
		return (0);
	else
		return (1);
}