#pragma once

# include <iostream>

namespace Libunit
{
	/* -------------------------------------------------------------------------- */
	/*                                   Colors                                   */
	/* -------------------------------------------------------------------------- */
	# define RESET	"\033[0m"
	# define BLACK	"\033[0;30m"
	# define RED	"\033[0;31m"
	# define GREEN	"\033[0;32m"
	# define YELLOW	"\033[0;33m"
	# define BLUE	"\033[0;34m"
	# define PURPLE	"\033[0;35m"
	# define CYAN	"\033[0;36m"
	# define WHITE	"\033[0;37m"
	# define GRAY	"\033[0;30m"

	/* -------------------------------------------------------------------------- */
	/*                                 Backgrounds                                */
	/* -------------------------------------------------------------------------- */
	# define B_BLACK	"\033[40m"
	# define B_RED		"\033[41m"
	# define B_GREEN	"\033[42m"
	# define B_YELLOW	"\033[43m"
	# define B_BLUE		"\033[44m"
	# define B_PURPLE	"\033[45m"
	# define B_CYAN		"\033[46m"
	# define B_WHITE	"\033[47m"

	/* -------------------------------------------------------------------------- */
	/*                                   Styles                                   */
	/* -------------------------------------------------------------------------- */
	# define BOLD		"\033[1;37m"

	typedef struct s_FinalResult
	{
		int	total_tests;
		int	tests_passed;
		int	routine_passed;
		int	total_routine;
	}	t_FinalResult;
	void	Redirect_log(void);
	int		Check_output(std::string expected);
}
