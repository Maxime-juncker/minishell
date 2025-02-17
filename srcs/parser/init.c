#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

static int	init_cmd(t_command *cmd, char *cmd_str, int is_last, int nb)
{
	char		**paths;
	static int	pipefd[2] = {-1};
	int			i;

	cmd->fd_in = 0;
	cmd->fd_out = 1;
	if (pipefd[0] != -1)
		cmd->fd_in = pipefd[0];
	if (pipe(pipefd) != -1)
		cmd->fd_out = pipefd[1];
	else
		return (cleanup_arr((void **)cmd->args), 1);
	cmd->args = ft_split_1space(cmd_str, ' ');
	if (!cmd->args)
		return (1);
	redir(cmd, cmd_str, is_last, nb);
	return (0);
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
		return (cleanup_arr((void **)commands), 127);
	i = 0;
	while (i < table->n_commands)
	{
		if (init_cmd(&table->commands[i], commands[i],
				i == table->n_commands - 1, i))
			return (cleanup_arr((void **)commands), free(table->commands), 127);
		i++;
	}
	cleanup_arr((void **)commands);
	return (0);
}
