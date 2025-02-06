#include "tests.hpp"

int	synt_err_1( void )
{
	const char *exepted_file[]
	{
		"minishell$ syntax error near unexpected token `newline\'",
	};

	Libunit::Redirect_log();
	if (check_cmd(">") == SYNTAX_ERR && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_2( void )
{
	const char *exepted_file[]
	{
		"minishell$ syntax error near unexpected token `newline\'",
	};

	Libunit::Redirect_log();
	if (check_cmd(">>") == SYNTAX_ERR && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_3( void )
{
	const char *exepted_file[]
	{
		"minishell$ syntax error near unexpected token `newline\'",
	};

	Libunit::Redirect_log();
	if (check_cmd("<") == SYNTAX_ERR && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_4( void )
{
	const char *exepted_file[]
	{
		"minishell$ syntax error near unexpected token `newline\'",
	};

	Libunit::Redirect_log();
	if (check_cmd("<<") == SYNTAX_ERR && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_5( void )
{
	const char *exepted_file[]
	{
		"minishell$ syntax error near unexpected token `newline\'",
	};

	Libunit::Redirect_log();
	if (check_cmd("<>") == SYNTAX_ERR && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_6( void )
{
	const char *exepted_file[]
	{
		"minishell$ syntax error near unexpected token `>>\'",
	};

	Libunit::Redirect_log();
	if (check_cmd(">>>>>") == SYNTAX_ERR && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_7( void )
{
	const char *exepted_file[]
	{
		"minishell$ syntax error near unexpected token `>>\'",
	};

	Libunit::Redirect_log();
	if (check_cmd(">>>>>>>>>>>>>>>") == SYNTAX_ERR && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_8( void )
{
	const char *exepted_file[]
	{
		"minishell$ syntax error near unexpected token `<<\'",
	};

	Libunit::Redirect_log();
	if (check_cmd("<<<<<<<<<<<<") == SYNTAX_ERR && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_9( void )
{
	const char *exepted_file[]
	{
		"minishell$ syntax error near unexpected token `>\'",
	};

	Libunit::Redirect_log();
	if (check_cmd("> > > > >") == SYNTAX_ERR && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_10( void )
{
	const char *exepted_file[]
	{
		"minishell$ syntax error near unexpected token `>>\'",
	};

	Libunit::Redirect_log();
	if (check_cmd(">>>> >> >> >>") == SYNTAX_ERR && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}


int	synt_err_11( void )
{
	const char *exepted_file[]
	{
		"minishell$ /: Is a directory",
	};

	Libunit::Redirect_log();
	if (check_cmd("/") == IS_DIR && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_12( void )
{
	const char *exepted_file[]
	{
		"minishell$ //: Is a directory",
	};

	Libunit::Redirect_log();
	if (check_cmd("//") == IS_DIR && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_13( void )
{
	const char *exepted_file[]
	{
		"minishell$ /./././...//: No such file or directory",
	};

	Libunit::Redirect_log();
	if (check_cmd("/./././...//") == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_14( void )
{
	const char *exepted_file[]
	{
		"minishell$ ///: Is a directory",
	};

	Libunit::Redirect_log();
	if (check_cmd("///") == IS_DIR && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_15( void )
{
	const char *exepted_file[]
	{
		"minishell$ -: command not found",
	};

	Libunit::Redirect_log();
	if (check_cmd("-") == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_16( void )
{
	const char *exepted_file[]
	{
		"minishell$ syntax error near unexpected token `|\'",
	};

	Libunit::Redirect_log();
	if (check_cmd("|") == SYNTAX_ERR && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_17( void )
{
	const char *exepted_file[]
	{
		"minishell$ syntax error near unexpected token `|\'",
	};

	Libunit::Redirect_log();
	if (check_cmd("| test") == SYNTAX_ERR && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_18( void )
{
	const char *exepted_file[]
	{
		"minishell$ syntax error near unexpected token `|\'",
	};

	Libunit::Redirect_log();
	if (check_cmd("| | |") == SYNTAX_ERR && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_19( void )
{
	const char *exepted_file[]
	{
		"minishell$ syntax error near unexpected token `||\'",
	};

	Libunit::Redirect_log();
	if (check_cmd("||") == SYNTAX_ERR && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_20( void )
{
	const char *exepted_file[]
	{
		"minishell$ syntax error near unexpected token `||\'",
	};

	Libunit::Redirect_log();
	if (check_cmd("|||||||||||") == SYNTAX_ERR && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_21( void )
{
	const char *exepted_file[]
	{
		"minishell$ syntax error near unexpected token `|\'",
	};

	Libunit::Redirect_log();
	if (check_cmd(">>|><") == SYNTAX_ERR && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_22( void )
{
	const char *exepted_file[]
	{
		"minishell$ hola: command not found",
	};

	Libunit::Redirect_log();
	if (check_cmd("\"hola\"") == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_23( void )
{
	const char *exepted_file[]
	{
		"minishell$ hola: command not found",
	};

	Libunit::Redirect_log();
	if (check_cmd("hola\'") == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_24( void )
{
	const char *exepted_file[]
	{
		"minishell$ hola: command not found",
	};

	Libunit::Redirect_log();
	if (check_cmd("hola") == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_25( void )
{
	const char *exepted_file[]
	{
		"minishell$ hola: command not found",
	};

	Libunit::Redirect_log();
	if (check_cmd("hola boula badaboum") == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}

int	synt_err_26( void )
{
	const char *exepted_file[]
	{
		"minishell$ Makefile: command not found",
	};

	Libunit::Redirect_log();
	if (check_cmd("Makefile") == NOT_FOUND && Libunit::CheckFile("log.txt", exepted_file, 1) == 0)
		return (0);
	else
		return (1);
}
