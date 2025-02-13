#include "commands.hpp"

int	redir_in( void )
{
	const char *exepted_file[]
	{
		"test",
	};
	t_command_table	table;
	table.env = environ;

	init_table((char *)"echo test > 1.txt", &table, 0);
	run_pipeline(&table);

	Libunit::Redirect_log();

	init_table((char *)"cat < 1.txt", &table, 0);
	run_pipeline(&table);
	if (Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}