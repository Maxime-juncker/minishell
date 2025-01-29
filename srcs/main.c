#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

void	init_table(char *line, char **env, t_command_table *table)
{
	t_command	cmd;
	int			pipefd[2];
	char		**commands;
	int			i;
	int			j;
	int			fd;

	commands = ft_split(line, '|');
	if (!commands)
		return ;
	table->n_commands = 0;
	while (commands[table->n_commands])
		table->n_commands++;
	table->commands = malloc(sizeof(t_command) * table->n_commands);
	if (!table->commands)
		return ;

	i = 0;
	while (i < table->n_commands)
	{
		table->commands[i].args = ft_split(commands[i], ' ');
		if (!table->commands[i].args)
			return ;
		table->commands[i].n_args = 0;
		while (table->commands[i].args[table->commands[i].n_args])
			table->commands[i].n_args++;
		table->commands[i].path = get_cmd_path(get_paths(env), table->commands[i]);

		if (i < table->n_commands - 1 && pipe(pipefd) == -1)
			return ;

		table->commands[i].fd_in = (i == 0) ? STDIN_FILENO : pipefd[0];
		table->commands[i].fd_out = (i == table->n_commands - 1) ? STDOUT_FILENO : pipefd[1];

		j = 0;
		while (j < table->commands[i].n_args)
		{
			if (table->commands[i].args[j][0] == '<')
				table->commands[i].fd_in = open(table->commands[i].args[j + 1], O_RDONLY);
			else if (table->commands[i].args[j][0] == '>')
			{
				fd = open(table->commands[i].args[j + 1], O_CREAT | O_TRUNC | O_WRONLY, 0777);
				if (fd == -1)
					return ;
				table->commands[i].fd_out = fd;
			}
			j++;
		}
		i++;
	}
}

void print_table(t_command_table *table)
{
	int i = 0;
	int j = 0;

    while (i < table->n_commands)
    {
        j = 0;
        while (j < table->commands[i].n_args)
        {
            printf("%s\n", table->commands[i].args[j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_command_table table;

	(void)ac;
	(void)av;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		add_history(line);
		if (!strncmp(line, "exit", 4))
		{
			free(line);
			break ;
		}
		init_table(line, env, &table);
		print_table(&table);
		free(line);
	}
	return (0);
}

