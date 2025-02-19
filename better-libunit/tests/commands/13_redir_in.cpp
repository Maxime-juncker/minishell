#include "commands.hpp"

int	redir_in( void )
{
	const char *exepted_file[]
	{
		"test",
	};
	t_command_table	table;
	table.env = duplicate_env(environ);
	table.exp = duplicate_env(environ);;
	int	code;

	init_table(process_line("echo test > 1.txt", table.env, &code), &table);
	run_pipeline(&table);

	Libunit::Redirect_log();

	init_table(process_line("cat < 1.txt", table.env, &code), &table);
	run_pipeline(&table);
	if (Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}