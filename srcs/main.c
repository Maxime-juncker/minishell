#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

void	new_prompt(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signal(int sig)
{
	(void)sig;
	printf("\n");
	new_prompt();
}

int	main(int ac, char **av, char **env)
{
	char			*line;
	t_command_table	table;
	int				last_cmd;

	(void)ac;
	(void)av;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	table.env = env;
	last_cmd = 0;
	while (1)
	{
		line = readline("\033[0mminishell$ ");
		if (check_cmd(line) == SYNTAX_ERR)
			continue ;
		if (line && !ft_strncmp(line, "\n", ft_strlen(line)))
			new_prompt();
		else if (!line || !ft_strncmp(line, "exit", ft_strlen(line)) && ft_strlen(line) == 4)
			return (0);
		last_cmd = init_table(line, env, &table, last_cmd);
		if (last_cmd != 127)
			last_cmd = run_pipeline(&table);
		add_history(line);
		free(line);
	}
	return (0);
}
