#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <unistd.h>

int	main(int ac, char **av, char **env)
{
	char			*line;
	t_command_table	table;

	(void)ac;
	(void)av;
	while (1)
	{
		line = readline("\033[0mminishell$ ");
		if (!line)
			break ;
		add_history(line);
		if (!ft_strncmp(line, "exit", strlen(line)))
		{
			free(line);
			break ;
		}
		if (init_table(line, env, &table))
			run_pipeline(table);
		free(line);
	}
	return (0);
}
