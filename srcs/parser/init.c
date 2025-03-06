/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:25:59 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/06 12:12:12 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	create_arg(char **cmd_arg, char *str)
{
	char	*arg;
	int		i;
	int		quote;

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
	if (malloc_assert(arg, __FILE__, __LINE__, __FUNCTION__) != 0)
		return (MALLOC_ERR);
	ft_strlcpy(arg, str, i + 1);
	*cmd_arg = arg;
	return (0);
}

static int	get_args(t_command *cmd, char *cmd_str)
{
	int		i;
	int		quote;
	int		new_arg;
	int		n_args;

	cmd->args = malloc(sizeof(char *) * count_args(cmd_str));
	if (malloc_assert(cmd->args, __FILE__, __LINE__, __FUNCTION__) != 0)
		return (MALLOC_ERR);
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
		if (new_arg && create_arg(&cmd->args[n_args++], &cmd_str[i])
			== MALLOC_ERR)
			return (free(cmd->args), MALLOC_ERR);
		new_arg = (!quote && cmd_str[i] == ' ' && cmd_str[i + 1]);
		i++;
	}
	return (cmd->args[n_args] = NULL, 0);
}

static int	init_cmd(t_command *cmd, char *cmd_str, int is_last, int i)
{
	static int	pipefd[2] = {-1};

	cmd->fd_in = 0;
	cmd->fd_out = 1;
	if (pipefd[0] != -1)
		cmd->fd_in = pipefd[0];
	if (is_last == 0 && pipe(pipefd) != -1)
		cmd->fd_out = pipefd[1];
	else if (is_last == 0)
		return (perror("Failed pipe"), MALLOC_ERR);
	if (get_args(cmd, cmd_str) == MALLOC_ERR)
		return (MALLOC_ERR);
	if (redir(cmd) != 0)
		return (cleanup_arr((void **)cmd->args), MALLOC_ERR);
	if (!i && !ft_strchr(cmd_str, '<'))
		cmd->fd_in = 0;
	if (is_last && !ft_strchr(cmd_str, '>'))
		cmd->fd_out = 1;
	return (0);
}

int	init_table(char *line, t_command_table *table)
{
	char	**commands;
	size_t	i;

	table->n_commands = 0;
	commands = ft_split_pipe(line);
	free(line);
	if (malloc_assert(commands, __FILE__, __LINE__, __FUNCTION__) != 0)
		return (MALLOC_ERR);
	while (commands[table->n_commands])
		table->n_commands++;
	table->commands = malloc(sizeof(t_command) * table->n_commands);
	if (malloc_assert(table->commands, __FILE__, __LINE__, __FUNCTION__) != 0)
		return (cleanup_arr((void **)commands), MALLOC_ERR);
	i = 0;
	while (i < table->n_commands)
	{
		table->commands[i].env = table->env;
		table->commands[i].code = table->code;
		if (init_cmd(&table->commands[i], commands[i],
				i == table->n_commands - 1, i) == MALLOC_ERR)
			return (cleanup_arr((void **)commands), table->n_commands = i,
				cleanup_table(table), MALLOC_ERR);
		i++;
	}
	return (cleanup_arr((void **)commands), 0);
}
