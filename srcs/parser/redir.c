/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:09:45 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/20 12:44:31 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_command(t_command *cmd)
{
	char	**temp;
	int		i;
	int		j;

	temp = malloc(sizeof(char *) * (cmd->n_args + 1));
	if (malloc_assert(temp, __FILE__, __LINE__, __FUNCTION__) == MALLOC_ERR)
		return (close_fds(*cmd), MALLOC_ERR);
	i = 0;
	j = 0;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] != '>' && cmd->args[i][0] != '<')
		{
			temp[j] = remove_quotes_pair(cmd->args[i]);
			free(cmd->args[i++]);
			if (malloc_assert(temp[j++], __FILE__, __LINE__, __FUNCTION__) != 0)
				return (free(cmd->args), cmd->args = temp, MALLOC_ERR);
		}
		else
		{
			free(cmd->args[i++]);
			free(cmd->args[i++]);
		}
	}
	return (free(cmd->args), temp[j] = NULL, cmd->args = temp, 0);
}

static int	handle_fd(t_command_table *table, t_command *cmd, char *file,
	char *arg)
{
	if (arg[0] == '>')
	{
		if (cmd->fd_out > 1)
			close(cmd->fd_out);
		if (arg[0] == arg[1])
			cmd->fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			cmd->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->fd_out == -1)
		{
			ft_dprintf(2, "%sminishell: %s: Permission denied\n%s",
				RED, file, RESET);
			table->code = 1;
			return (1);
		}
	}
	else if (arg[0] != arg[1])
	{
		if (cmd->fd_in > 1)
			close(cmd->fd_in);
		if (check_redir_in(file, -1) != 0)
			return (close_all_fds(table), table->code = 1, 1);
		cmd->fd_in = open(file, O_RDONLY, 0644);
	}
	return (0);
}

static int	redir(t_command_table *table, t_command *cmd)
{
	int		i;
	char	*file;

	i = 0;
	cmd->n_args = 0;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] == '>' || cmd->args[i][0] == '<')
		{
			file = remove_quotes_pair(cmd->args[i + 1]);
			if (malloc_assert(file, __FILE__, __LINE__, __FUNCTION__) != 0)
				return (MALLOC_ERR);
			if (handle_fd(table, cmd, file, cmd->args[i]) == 1)
				return (free(file), table->code = 1, 1);
			free(file);
			i++;
		}
		else
			cmd->n_args++;
		i++;
	}
	return (update_command(cmd));
}

static int	handle_pipe(t_command_table *table, t_command *cmd, size_t n)
{
	static int	pipefd[2] = {-1};

	if (pipefd[0] != -1)
	{
		if (cmd->fd_in > 1)
			close(cmd->fd_in);
		cmd->fd_in = pipefd[0];
	}
	if (n != table->n_commands - 1 && pipe(pipefd) != -1)
	{
		if (cmd->fd_out > 1)
			close(cmd->fd_out);
		cmd->fd_out = pipefd[1];
	}
	else if (n != table->n_commands - 1)
		return (perror("Failed pipe"), MALLOC_ERR);
	if (n == table->n_commands - 1)
		pipefd[0] = -1;
	return (0);
}

int	init_redir(t_command_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->n_commands)
	{
		if (handle_pipe(table, &table->commands[i], i) != 0)
		{
			cleanup_table(table);
			return (MALLOC_ERR);
		}
		if (redir(table, &table->commands[i]) != 0)
		{
			cleanup_table(table);
			return (MALLOC_ERR);
		}
		i++;
	}
	return (0);
}
