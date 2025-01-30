#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

void	new_prompt()
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		new_prompt();
	}
}
int	main(int ac, char **av, char **env)
{
	char			*line;
	t_command_table	table;

	(void)ac;
	(void)av;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	table.env = env;
	while (1)
	{
		line = readline("\033[0mminishell$ ");
		if (line && !ft_strncmp(line, "\n", strlen(line)))
			new_prompt();
		else if (!line || !ft_strncmp(line, "exit", strlen(line)))
			return (0);
		else if (init_table(line, env, &table))
			run_pipeline(&table);
		add_history(line);
		free(line);
	}
	return (0);
}
