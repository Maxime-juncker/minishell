#include "tests.hpp"

static int code;
static t_command_table table = {(char*)"minishell", NULL, 0, duplicate_env(environ), duplicate_env(environ), -1, 0};

int	dolars_01( void )
{
	const char *exepted_file[]
	{
		"0",
	};

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
	if (check_path(ft_strdup("$"), environ) == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
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
	init_table(process_line("\"$HOMEgfehgeuohge\"", environ, &code), &table);
	if (check_path(table.commands[0].args[0], environ) == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	dolars_07( void )
{
	return (1);
	// const char *exepted_file[]
	// {
	// 	"\033[0;31mminishell: $HOMEgfehgeuohge: command not found",
	// };

	// Libunit::Redirect_err();
	// check_path(process_line("$HOMEgfehgeuohge", environ, &code), environ);
	// if (code == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
	// 	return (0);
	// else
	// 	return (1);
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