#include "commands.hpp"

int	expanded_var( void )
{

	const char *exepted_file[]
	{
		"ubuntu",
	};

	t_command_table	table;
	table.env = environ;

	Libunit::Redirect_log();
	init_table(process_line("echo $DESKTOP_SESSION", environ), environ, &table, 0);
	run_pipeline(&table);
	if (Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}