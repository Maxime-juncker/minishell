#include "tests.hpp"

static int code;

int	dolars_01( void )
{
	const char *exepted_file[]
	{
		"0",
	};

	t_command_table	table;
		table.env = duplicate_env(environ);
	table.exp = duplicate_env(environ);;

	init_table(process_line("echo $?", environ, &code), &table);
	Libunit::Redirect_log();
	run_pipeline(&table, NULL);

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
		table.env = duplicate_env(environ);
	table.exp = duplicate_env(environ);;

	init_table(process_line("echo $?$?", environ, &code), &table);
	Libunit::Redirect_log();
	run_pipeline(&table, NULL);

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
		table.env = duplicate_env(environ);
	table.exp = duplicate_env(environ);;

	init_table(process_line("echo ?$DESKTOP_SESSION", environ, &code), &table);
	Libunit::Redirect_log();
	run_pipeline(&table, NULL);

	if (Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	dolars_04( void )
{
	const char *exepted_file[]
	{
		"\033[0;31mminishell: $: command not found",
	};

	Libunit::Redirect_err();
	if (check_cmd_line(ft_strdup("$"), &code) == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
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
		table.env = duplicate_env(environ);
	table.exp = duplicate_env(environ);;

	init_table(process_line("echo $HOMEgfehgeuohge", environ, &code), &table);
	Libunit::Redirect_log();
	run_pipeline(&table, NULL);

	if (Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	dolars_06( void )
{
	const char *exepted_file[]
	{
		"\033[0;31mminishell: : command not found",
	};

	Libunit::Redirect_err();

	process_line("\"$HOMEgfehgeuohge\"", environ, &code);
	if (code == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	dolars_07( void )
{
	const char *exepted_file[]
	{
		"\033[0;31mminishell: $HOMEgfehgeuohge: command not found",
	};

	Libunit::Redirect_err();
	if (check_cmd_line(ft_strdup("$HOMEgfehgeuohge"), &code) == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	dolars_08( void )
{
	char *line = process_line("$DONTEXIST", environ, &code);
	if (line == NULL)
		return (0);
	else
		return (1);
}

int	dolars_09( void )
{
	char *line = process_line("$DONTEXIST$VAR", environ, &code);
	if (line == NULL)
		return (0);
	else
		return (1);
}