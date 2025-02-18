#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

static int	count_args(char *cmd_str)
{
	int	n_args;
	int	i;
	int	quote;

	quote = 0;
	n_args = 1;
	i = 0;
	while (cmd_str[i])
	{
		if (cmd_str[i] == '\'' || cmd_str[i] == '\"')
			quote = toggle_quote(quote, cmd_str[i]);
		if (!quote && cmd_str[i] == ' ' && cmd_str[i + 1])
			n_args++;
		i++;
	}
	return (n_args + 1);
}

static char	*create_arg(char *str)
{
	char	*arg;
	int		i;
	int		quote;
	char	*temp;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			quote = toggle_quote(quote, str[i]);
		if (!quote && str[i] == ' ')
			break ;
		i++;
	}
	arg = malloc(sizeof(char) * (i + 1));
	if (!arg)
		return (NULL);
	ft_strlcpy(arg, str, i + 1);
	temp = remove_quotes_pair(arg);
	free(arg);
	return (temp);
}

static void	get_args(t_command *cmd, char *cmd_str)
{
	char	**args;
	int		i;
	int		quote;
	int		new_arg;
	int		n_args;

	cmd->args = malloc(sizeof(char *) * count_args(cmd_str));
	if (!cmd->args)
		return ;
	quote = 0;
	i = 0;
	new_arg = 1;
	n_args = 0;
	while (cmd_str[i] == ' ')
		i++;
	while (cmd_str[i])
	{
		if (cmd_str[i] == '\'' || cmd_str[i] == '\"')
			quote = toggle_quote(quote, cmd_str[i]);
		if (new_arg)
		{
			cmd->args[n_args] = create_arg(&cmd_str[i]);
			if (!cmd->args[n_args])
				cleanup_arr((void **)cmd->args);
			n_args++;
		}
		new_arg = 0;
		if (!quote && cmd_str[i] == ' ' && cmd_str[i + 1])
		{
			new_arg = 1;
		}
		i++;
	}
	cmd->args[n_args] = NULL;
}

static int	init_cmd(t_command *cmd, char *cmd_str, int is_last, int nb)
{
	char		**paths;
	static int	pipefd[2] = {-1};
	int			i;

	cmd->fd_in = 0;
	cmd->fd_out = 1;
	if (pipefd[0] != -1)
	{
		cmd->fd_in = pipefd[0];
	}
	if (is_last == 0)
	{
		if (pipe(pipefd) != -1)
			cmd->fd_out = pipefd[1];
		else
			return (cleanup_arr((void **)cmd->args), 1);
	}
	get_args(cmd, cmd_str);
	if (!cmd->args)
		return (MALLOC_ERR);
	redir(cmd, cmd_str, is_last, nb);
	return (0);
}

int	init_table(char *line, t_command_table *table)
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
	free(line);
	return (0);
}
