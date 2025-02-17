#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

void	print_pid(void)
{
	printf("%s%d: %s", GRAY, getpid(), RESET);
}

void	new_prompt(t_command_table *table)
{
	char	*line;
	char	*process_cmd;
	static int	code = 0;
	int	tmp;

	g_signal_received = 0;
	line = readline("\033[0;32mminishell$\033[0m ");
	if (g_signal_received)
	{
		if (g_signal_received == SIGINT)
			code = 130;
		g_signal_received = 0;
		return;
	}
	if (!line || (ft_strlen(line) == 4 && !ft_strncmp(line, "exit", 4)))
	{
		cleanup_arr((void **)table->env);
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	else if (ft_strncmp(line, "\n", ft_strlen(line)))
		add_history(line);
	if (ft_strncmp(line, "\n", ft_strlen(line)) && \
		ft_strncmp(line, "!", ft_strlen(line))
		&& ft_strncmp(line, ":", ft_strlen(line)))
	{
		process_cmd = process_line(line, table->env, &code);
		free(line);
		if (!process_cmd)
		{
			return ;
		}
		if (code == SYNTAX_ERR || code == IS_DIR || code == NOT_FOUND)
		{
			free(process_cmd);
			return ;
		}
		else if (code == MALLOC_ERR)
		{
			cleanup_arr((void **)table->env);
			error("malloc failed");
			exit(EXIT_FAILURE);
		}
		else
		{
			tmp = init_table(process_cmd, table);
			free(process_cmd);
			if (tmp == 0)
				code = run_pipeline(table) % 255;
		}
	}
}

void check_piped_execution(void)
{
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
	{
		error("minishell: must run interactively (need a tty)");
		exit(EXIT_FAILURE);
	}
}

int	check_interrupt( void )
{
	if (g_signal_received)
		rl_done = 1;
	return (0);
}

int	main(void)
{
	char			*line;
	t_command_table	table;
	char			*process_cmd;

	rl_event_hook = check_interrupt;
	check_piped_execution();
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	table.env = duplicate_env(__environ);
	table.exp = duplicate_env(__environ);
	if (table.env == NULL || table.exp == NULL)
		return (EXIT_FAILURE);
	while (1)
	{
		new_prompt(&table);
	}
	exit (0);
}

