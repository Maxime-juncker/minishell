#include "commands.hpp"

int	expanded_var( void )
{

	const char *exepted_file[]
	{
		"ubuntu",
	};
	int	code;
	t_command_table	table;
	table.env = duplicate_env(environ);
	table.exp = duplicate_env(environ);

	Libunit::Redirect_log();
	init_table(process_line("echo $DESKTOP_SESSION", environ, &code), &table);
	run_pipeline(&table);
	if (Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}