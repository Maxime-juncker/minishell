
#include "echo.hpp"

int	echo_01( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)"echo", &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::Check_output("\n") == 0)
		return (0);
	else
		return (1);
}

int	echo_02( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)"echo -n", &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::Check_output("") == 0)
		return (0);
	else
		return (1);
}

int	echo_03( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)"echo Test", &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::Check_output("Test\n") == 0)
		return (0);
	else
		return (1);
}

int	echo_04( void )
{
	const char *exepted_file[]
	{
		"minishell: echoHola: command not found",
	};

	Libunit::Redirect_log();
	if (check_cmd_line("echoHola") == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	echo_05( void )
{
	const char *exepted_file[]
	{
		"minishell: echo-nHola: command not found",
	};

	Libunit::Redirect_log();
	if (check_cmd_line("echo-nHola") == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	echo_07( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)"echo -n test", &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::Check_output("test") == 0)
		return (0);
	else
		return (1);
}

int	echo_08( void )
{
	const char *exepted_file[]
	{
		"Test",
	};

	t_command_table	table;
	table.env = environ;

	init_table(process_line("echo \"-n\" Test", environ, NULL), &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	echo_09( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)"echo -ntest", &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::Check_output("-ntest\n") == 0)
		return (0);
	else
		return (1);
}

int	echo_10( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)"echo test -n", &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::Check_output("test -n\n") == 0)
		return (0);
	else
		return (1);
}

int	echo_11( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)"echo test1 test2 test3", &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::Check_output("test1 test2 test3\n") == 0)
		return (0);
	else
		return (1);
}

int	echo_12( void )
{
	t_command_table	table;
	table.env = environ;

	init_table(process_line("echo                test", environ, NULL), &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::Check_output("test\n") == 0)
		return (0);
	else
		return (1);
}

int	echo_13( void )
{
	t_command_table	table;
	table.env = environ;

	init_table(process_line("echo test1     test2    test3", environ, NULL), &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::Check_output("test1 test2 test3\n") == 0)
		return (0);
	else
		return (1);
}

int	echo_14( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)"echo    \\n test", &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::Check_output("n test") == 0)
		return (0);
	else
		return (1);
}

int	echo_15( void )
{
	t_command_table	table;
	table.env = environ;

	init_table(process_line("echo \"         \" | cat -e", environ, NULL), &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::Check_output("         $\n") == 0)
		return (0);
	else
		return (1);
}

int	echo_16( void )
{
	t_command_table	table;
	table.env = environ;

	init_table(process_line("echo           | cat -e", environ, NULL), &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::Check_output("$\n") == 0)
		return (0);
	else
		return (1);
}

int	echo_17( void )
{
	t_command_table	table;
	table.env = environ;

	init_table(process_line("\"\"\'\'echo hola\"\"\'\'\'\' que\"\"\'\' tal\"\"\'\'", environ, NULL), &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::Check_output("hola que tal\n") == 0)
		return (0);
	else
		return (1);
}

int	echo_18( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)"echo -n -n", &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::Check_output("") == 0)
		return (0);
	else
		return (1);
}

int	echo_19( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)"echo -n -n test oui", &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::Check_output("test oui") == 0)
		return (0);
	else
		return (1);
}

int	echo_20( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)"echo -p", &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::Check_output("-p\n") == 0)
		return (0);
	else
		return (1);
}

int	echo_21( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)"echo -nnnnnnnn", &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::Check_output("") == 0)
		return (0);
	else
		return (1);
}

int	echo_22( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)"echo -nnnn -n -nnnn", &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::Check_output("") == 0)
		return (0);
	else
		return (1);
}

int	echo_23( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)"echo -nnnn-n -nnnn", &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::Check_output("-nnnn-n -nnnn\n") == 0)
		return (0);
	else
		return (1);
}

int	echo_24( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)"echo -n -nnn test -n -nnnn", &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::Check_output("test -n -nnnn") == 0)
		return (0);
	else
		return (1);
}

int	echo_25( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)"echo -n -nnn-nnnn", &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::Check_output("-nnn-nnnn") == 0)
		return (0);
	else
		return (1);
}

int	echo_26( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)"echo -----n", &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::Check_output("-----n\n") == 0)
		return (0);
	else
		return (1);
}

int	echo_27( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)"echo -nnn -----n", &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::Check_output("-----n") == 0)
		return (0);
	else
		return (1);
}

int	echo_28( void )
{
	t_command_table	table;
	table.env = environ;

	init_table((char *)"echo -nnn -----nn---nnnn", &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::Check_output("-----nn---nnnn") == 0)
		return (0);
	else
		return (1);
}

int	echo_29( void )
{
	const char *exepted_file[]
	{
		"$",
	};

	t_command_table	table;
	table.env = environ;

	Libunit::Redirect_log();
	init_table(process_line("echo $", environ, NULL), &table, 0);
	run_pipeline(&table);

	if (Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	echo_30( void )
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

int	echo_31( void )
{
	const char *exepted_file[]
	{
		"0$",
	};

	t_command_table	table;
	table.env = environ;

	init_table(process_line("echo $?$", environ, NULL), &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	echo_32( void )
{
	const char *exepted_file[]
	{
		"0",
	};

	t_command_table	table;
	table.env = environ;

	Libunit::Redirect_log();
	init_table(process_line("echo $? | echo $? | echo $?", environ, NULL), &table, 0);
	run_pipeline(&table);

	if (Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	echo_33( void )
{
	const char *exepted_file[]
	{
		"$:$=$",
	};

	t_command_table	table;
	table.env = environ;

	init_table(process_line("echo $:$= | cat -e", environ, NULL), &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	echo_34( void )
{
	const char *exepted_file[]
	{
		" $ $",
	};

	t_command_table	table;
	table.env = environ;

	init_table(process_line("echo \" $ \" | cat -e", environ, NULL), &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	echo_35( void )
{
	const char *exepted_file[]
	{
		" $ $",
	};

	t_command_table	table;
	table.env = environ;

	init_table(process_line("echo \' $ \' | cat -e", environ, NULL), &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	echo_36( void )
{
	const char *exepted_file[]
	{
		"test",
	};

	t_command_table	table;
	table.env = environ;

	init_table(process_line("echo \"$DONTEXIST\"test", environ, NULL), &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	echo_37( void )
{
	const char *exepted_file[]
	{
		"test",
	};

	t_command_table	table;
	table.env = environ;

	init_table(process_line("echo \"$DONTEXIST\"\"test\"", environ, NULL), &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	echo_38( void )
{
	const char *exepted_file[]
	{
		" test",
	};

	t_command_table	table;
	table.env = environ;

	init_table(process_line("echo \"$DONTEXIST\" \"test\"", environ, NULL), &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	echo_39( void )
{
	const char *exepted_file[]
	{
		" test",
	};

	t_command_table	table;
	table.env = environ;

	init_table(process_line("echo \"$DONTEXIST\"       \"test\"", environ, NULL), &table, 0);
	Libunit::Redirect_log();
	run_pipeline(&table);

	if (Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}
