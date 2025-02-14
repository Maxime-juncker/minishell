#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

void	handle_signal(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void check_piped_execution(void)
{
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
	{
		printf("minishell: must run interactively (need a tty)\n");
		exit(EXIT_FAILURE);
	}
}

int	main(void)
{
	char			*line;
	t_command_table	table;
	int				last_cmd;
	int				code;
	char			*process_cmd;

	check_piped_execution();
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	table.env = duplicate_env(__environ);
	if (table.env == NULL)
		return (EXIT_FAILURE);
	last_cmd = 0;
	while (1)
	{
		line = readline("\033[0mminishell$ ");
		if (!line || (ft_strlen(line) == 4 && !ft_strncmp(line, "exit", 4)))
		{
			cleanup_arr((void **)table.env);
			return (printf("exit\n"), 0);
		}
		else if (ft_strncmp(line, "\n", ft_strlen(line)))
			add_history(line);
		if (ft_strncmp(line, "\n", ft_strlen(line)) && ft_strncmp(line, "!", ft_strlen(line)) && ft_strncmp(line, ":", ft_strlen(line)))
		{
			process_cmd = process_line(line, table.env, &code);
			free(line);
			if (!process_cmd)
			{
				continue ;
			}
			if (code == SYNTAX_ERR || code == IS_DIR || code == NOT_FOUND)
			{
				free(process_cmd);
				continue ;
			}
			else if (code == MALLOC_ERR)
			{
				cleanup_arr((void **)table.env);
				error("malloc failed");
				exit(EXIT_FAILURE);
			}
			else
			{
				last_cmd = init_table(process_cmd, &table, last_cmd);
				free(process_cmd);
				if (last_cmd != 127)
					last_cmd = run_pipeline(&table);
			}
		}
	}
	return (0);
}

