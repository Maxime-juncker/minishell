#include "commands.hpp"

int	pipe_after_redir( void )
{
	const char *exepted_file[]
	{
		"0",
	};
	t_command_table	table;
	table.env = environ;
	init_table((char *)"echo test | wc -c > 1 | wc -l", &table);

	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}
