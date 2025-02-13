#include "tests.hpp"

int	input_new_line( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)"\n", &table, 0);

	Libunit::Redirect_log();
	run_pipeline(&table);
	if (Libunit::Check_output("\n") == 0)
		return (0);
	else
		return (1);
}

int	input_tabs( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)"\t", &table, 0);

	Libunit::Redirect_log();
	run_pipeline(&table);
	if (Libunit::Check_output("\n") == 0)
		return (0);
	else
		return (1);
}

int	input_exclamation( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)"!", &table, 0);

	Libunit::Redirect_log();
	run_pipeline(&table);
	if (Libunit::Check_output("\n") == 0)
		return (0);
	else
		return (1);
}

int	input_colon( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)":", &table, 0);

	Libunit::Redirect_log();
	run_pipeline(&table);
	if (Libunit::Check_output("\n") == 0)
		return (0);
	else
		return (1);
}