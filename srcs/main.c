#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

int	main(int argc, char **argv, char **env)
{
	t_command_table	table;

	(void)argc;
	(void)argv;
	check_piped_execution();
	init_env(&table, env);
	rl_event_hook = check_interrupt;
	signal(SIGINT, handle_signal);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, handle_signal);
	while (1)
	{
		new_prompt(&table);
	}
	exit(EXIT_SUCCESS);
}
