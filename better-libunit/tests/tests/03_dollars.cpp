#include "tests.hpp"

int	dolars_01( void )
{
	const char *exepted_file[]
	{
		"0",
	};

	t_command_table	table;
	table.env = environ;

	init_table(process_line("echo $?", environ, NULL), &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	dolars_02( void )
{
	const char *exepted_file[]
	{
		"00",
	};

	t_command_table	table;
	table.env = environ;

	init_table(process_line("echo $?$?", environ, NULL), &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	dolars_03( void )
{
	const char *exepted_file[]
	{
		"?ubuntu",
	};

	t_command_table	table;
	table.env = environ;

	init_table(process_line("echo ?$DESKTOP_SESSION", environ, NULL), &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	dolars_04( void )
{
	const char *exepted_file[]
	{
		"minishell: $: command not found",
	};

	Libunit::Redirect_log();
	if (check_cmd_line("$") == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	dolars_05( void )
{
	const char *exepted_file[]
	{
		"",
	};

	t_command_table	table;
	table.env = environ;

	init_table(process_line("echo $HOMEgfehgeuohge", environ, NULL), &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	dolars_06( void )
{
	const char *exepted_file[]
	{
		"minishell: : command not found",
	};

	Libunit::Redirect_log();
	if (check_cmd_line("\"$HOMEgfehgeuohge\"") == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	dolars_07( void )
{
	const char *exepted_file[]
	{
		"minishell: $HOMEgfehgeuohge: command not found",
	};

	Libunit::Redirect_log();
	if (check_cmd_line("$HOMEgfehgeuohge") == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	dolars_08( void )
{
	char *line = process_line("$DONTEXIST", environ, NULL);
	if (line == NULL)
		return (0);
	else
		return (1);
}

int	dolars_09( void )
{
	char *line = process_line("$DONTEXIST$VAR", environ, NULL);
	if (line == NULL)
		return (0);
	else
		return (1);
}