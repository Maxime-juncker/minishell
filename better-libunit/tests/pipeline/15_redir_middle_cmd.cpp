#include "commands.hpp"

int	redir_middle_cmd( void )
{
	const char *exepted_file[]
	{
		"5",
	};
	t_command_table	table;
	table.env = duplicate_env(environ);
	table.exp = duplicate_env(environ);;
	int	code;

	init_table(process_line("echo test | wc > tmp -c", table.env, &code), &table);
	run_pipeline(&table, NULL);

	Libunit::Redirect_log();

	init_table(process_line("cat tmp", table.env, &code), &table);
	run_pipeline(&table, NULL);
	if (Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}