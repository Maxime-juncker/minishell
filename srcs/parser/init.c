#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

static int	init_cmd(t_command *cmd, char *cmd_str, int is_last)
{
	char		**paths;
	static int	pipefd[2] = {-1};

	cmd->fd_in = 0;
	cmd->fd_out = 1;
	if (pipefd[0] != -1)
		cmd->fd_in = pipefd[0];
	cmd->args = ft_split_1space(cmd_str, ' ');
	if (!cmd->args)
		return (0);
	cmd->n_args = 0;
	while (cmd->args[cmd->n_args])
		cmd->n_args++;
	if (pipe(pipefd) != -1)
		cmd->fd_out = pipefd[1];
	else
	{
		cleanup_arr((void **)cmd->args);
		return (0);
	}
	redir(cmd, cmd_str, is_last);
	return (1);
}

int	init_table(char *line, t_command_table *table, int last_cmd)
{
	char	**commands;
	size_t	i;

	while (*line == ' ' || *line == '\t')
		line++;
	commands = ft_split(line, '|');
	if (!commands)
		return (127);
	table->n_commands = 0;
	while (commands[table->n_commands])
		table->n_commands++;
	table->commands = malloc(sizeof(t_command) * table->n_commands);
	if (!table->commands)
		return (free_all(commands), 127);
	i = 0;
	while (i < table->n_commands)
	{
		if (!init_cmd(&table->commands[i], commands[i], i == table->n_commands - 1))
			return (free_all(commands), free(table->commands), 127);
		i++;
	}
	free_all(commands);
	return (1);
}
