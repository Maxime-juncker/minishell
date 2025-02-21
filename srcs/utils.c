#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

void	init_env(t_command_table *table, char **env)
{
	table->env = duplicate_env(env);
	if (table->env == NULL)
		exit(EXIT_FAILURE);
	table->exp = duplicate_env(env);
	if (table->exp == NULL)
	{
		cleanup_arr((void **)table->env);
		exit(EXIT_FAILURE);
	}
}

void	handle_signal(int signal)
{
	g_signal_received = signal;
}

void	cleanup_table(t_command_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->n_commands)
	{
		cleanup_arr((void **)table->commands[i].args);
		i++;
	}
	free(table->commands);
}

char	*get_folder(void)
{
	char	*folder;
	char	*temp;

	folder = get_pwd();
	if (!folder)
		return (NULL);
	temp = folder;
	if (folder[1] != '\0')
	{
		while (*folder && ft_strchr(folder, '/') != 0)
		{
			folder++;
		}
	}
	folder = ft_strjoin(folder, ":");
	free(temp);
	return (folder);
}

void	check_piped_execution(void)
{
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
	{
		ft_dprintf(2, "minishell: must run interactively (need a tty)\n");
		exit(EXIT_FAILURE);
	}
}
