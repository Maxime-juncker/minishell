#include "tests.hpp"

static int code;
static t_command_table table = {(char*)"minishell", NULL, 0, duplicate_env(environ), duplicate_env(environ), -1};

int	synt_err_1( void )
{
	const char *exepted_file[]
	{
		"\033[0;31mminishell: syntax error near unexpected token `newline\'",
	};

	Libunit::Redirect_err();
	if (check_cmd_line(ft_strdup(">"), &code) == SYNTAX_ERR && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_2( void )
{
	const char *exepted_file[]
	{
		"\033[0;31mminishell: syntax error near unexpected token `newline\'",
	};

	Libunit::Redirect_err();
	if (check_cmd_line(ft_strdup(">>"), &code) == SYNTAX_ERR && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_3( void )
{
	const char *exepted_file[]
	{
		"\033[0;31mminishell: syntax error near unexpected token `newline\'",
	};

	Libunit::Redirect_err();
	if (check_cmd_line(ft_strdup("<"), &code) == SYNTAX_ERR && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_4( void )
{
	const char *exepted_file[]
	{
		"\033[0;31mminishell: syntax error near unexpected token `newline\'",
	};

	Libunit::Redirect_err();
	if (check_cmd_line(ft_strdup("<<"), &code) == SYNTAX_ERR && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_5( void )
{
	const char *exepted_file[]
	{
		"\033[0;31mminishell: syntax error near unexpected token `>\'",
	};

	Libunit::Redirect_err();
	if (check_cmd_line(ft_strdup("<>"), &code) == SYNTAX_ERR && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_6( void )
{
	Libunit::Redirect_err();
	if (check_cmd_line(ft_strdup(">>>>>"), &code) == SYNTAX_ERR)
		return (0);
	else
		return (1);
}

int	synt_err_7( void )
{
	Libunit::Redirect_err();
	if (check_cmd_line(ft_strdup(">>>>>>>>>>>>>>>"), &code) == SYNTAX_ERR)
		return (0);
	else
		return (1);
}

int	synt_err_8( void )
{
	Libunit::Redirect_err();
	if (check_cmd_line(ft_strdup("<<<<<<<<<<<<"), &code) == SYNTAX_ERR)
		return (0);
	else
		return (1);
}

int	synt_err_9( void )
{
	Libunit::Redirect_err();
	if (check_cmd_line(ft_strdup("> > > > >"), &code) == SYNTAX_ERR)
		return (0);
	else
		return (1);
}

int	synt_err_10( void )
{
	Libunit::Redirect_err();
	if (check_cmd_line(ft_strdup(">>>> >> >> >>"), &code) == SYNTAX_ERR)
		return (0);
	else
		return (1);
}


int	synt_err_11( void )
{
	const char *exepted_file[]
	{
		"\033[0;31mminishell: /: Is a directory",
	};

	Libunit::Redirect_err();
	if (check_path(ft_strdup("/"), environ) == IS_DIR && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_12( void )
{
	const char *exepted_file[]
	{
		"\033[0;31mminishell: //: Is a directory",
	};

	Libunit::Redirect_err();
	if (check_path(ft_strdup("//"), environ) == IS_DIR && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_13( void )
{
	const char *exepted_file[]
	{
		"\033[0;31mminishell: /./././...//: No such file or directory",
	};

	Libunit::Redirect_err();
	if (check_path(ft_strdup("/./././...//"), environ) == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_14( void )
{
	const char *exepted_file[]
	{
		"\033[0;31mminishell: ///: Is a directory",
	};

	Libunit::Redirect_err();
	if (check_path(ft_strdup("///"), environ) == IS_DIR && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_15( void )
{
	const char *exepted_file[]
	{
		"\033[0;31mminishell: -: command not found",
	};

	Libunit::Redirect_err();
	if (check_path(ft_strdup("-"), environ) == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_16( void )
{
	Libunit::Redirect_err();
	if (check_cmd_line(ft_strdup("|"), &code) == SYNTAX_ERR)
		return (0);
	else
		return (1);
}

int	synt_err_17( void )
{
	Libunit::Redirect_err();
	if (check_cmd_line(ft_strdup("| test"), &code) == SYNTAX_ERR)
		return (0);
	else
		return (1);
}

int	synt_err_18( void )
{
	Libunit::Redirect_err();
	if (check_cmd_line(ft_strdup("| | |"), &code) == SYNTAX_ERR)
		return (0);
	else
		return (1);
}

int	synt_err_19( void )
{
	Libunit::Redirect_err();
	if (check_cmd_line(ft_strdup("||"), &code) == SYNTAX_ERR)
		return (0);
	else
		return (1);
}

int	synt_err_20( void )
{
	Libunit::Redirect_err();
	if (check_cmd_line(ft_strdup("|||||||||||"), &code) == SYNTAX_ERR)
		return (0);
	else
		return (1);
}

int	synt_err_21( void )
{
	Libunit::Redirect_err();
	if (check_cmd_line(ft_strdup(">>|><"), &code) == SYNTAX_ERR)
		return (0);
	else
		return (1);
}

int	synt_err_22( void )
{
	const char *exepted_file[]
	{
		"\033[0;31mminishell: hola: command not found",
	};
	

	Libunit::Redirect_err();
	init_table(process_line("\"hola\"", table.env, &code), &table);
	if (check_path(table.commands->args[0], environ) == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_23( void )
{
	const char *exepted_file[]
	{
		"\033[0;31mminishell: hola': command not found",
	};

	Libunit::Redirect_err();
	init_table(process_line("\"hola\'\"", table.env, &code), &table);
	if (check_path(table.commands->args[0], environ) == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_24( void )
{
	const char *exepted_file[]
	{
		"\033[0;31mminishell: hola: command not found",
	};

	Libunit::Redirect_err();
	if (check_path(process_line("hola", environ, &code), environ) == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_25( void )
{
	const char *exepted_file[]
	{
		"\033[0;31mminishell: hola: command not found",
	};

	Libunit::Redirect_err();
	init_table(process_line("hola boula badaboum", table.env, &code), &table);
	if (check_path(table.commands->args[0], environ) == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_26( void )
{
	const char *exepted_file[]
	{
		"\033[0;31mminishell: Makefile: command not found",
	};

	Libunit::Redirect_err();
	if (check_path(process_line("Makefile", environ, &code), environ) == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_27( void )
{
	const char *exepted_file[]
	{
		"\033[0;31mminishell: holaoui: command not found",
	};

	Libunit::Redirect_err();
	init_table(process_line("hola\"\"oui", table.env, &code), &table);
	if (check_path(table.commands->args[0], environ) == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_28( void )
{
	const char *exepted_file[]
	{
		"\033[0;31mminishell: ho\'\'laoui: command not found",
	};

	Libunit::Redirect_err();
	init_table(process_line("ho\"\'\'\"la\'\'oui", table.env, &code), &table);
	if (check_path(table.commands->args[0], environ) == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_29( void )
{
	const char *exepted_file[]
	{
		"\033[0;31mminishell: \"hola\": command not found",
	};

	Libunit::Redirect_err();
	init_table(process_line("\'\"hola\"\'", table.env, &code), &table);
	if (check_path(table.commands->args[0], environ) == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_30( void )
{
	const char *exepted_file[]
	{
		"\033[0;31mminishell: \'hola\': command not found",
	};

	Libunit::Redirect_err();
	init_table(process_line("\"\'hola\'\"", table.env, &code), &table);
	if (check_path(table.commands->args[0], environ) == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_31( void )
{
	const char *exepted_file[]
	{
		"\033[0;31mminishell: \'ls\': command not found",
	};

	Libunit::Redirect_err();
	init_table(process_line("\"\'\"ls\"\'\"", table.env, &code), &table);
	if (check_path(table.commands->args[0], environ) == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_32( void )
{
	const char *exepted_file[]
	{
		"\033[0;31mminishell: \'\'/bin: No such file or directory",
	};

	Libunit::Redirect_err();
	init_table(process_line("\"\'\'\"/bin", table.env, &code), &table);
	if (check_path(table.commands->args[0], environ) == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_33( void )
{
	const char *exepted_file[]
	{
		"\033[0;31mminishell: e cho: command not found",
	};

	Libunit::Redirect_err();
	init_table(process_line("\"e\"\' c\'\"h\"\'o\'", table.env, &code), &table);
	if (check_path(table.commands->args[0], environ) == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_34( void )
{
	if (check_cmd_line(process_line("ls>1", environ, &code), &code) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_35( void )
{
	const char *exepted_file[]
	{
		"\033[0;31mminishell: : command not found",
	};

	Libunit::Redirect_err();
	init_table(process_line("\"$HOGNGERbrknie\"", table.env, &code), &table);
	check_cmd_line(process_line("\"$HOGNGERbrknie\"", environ, &code), &code);
	if (check_path(table.commands->args[0], environ) == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}