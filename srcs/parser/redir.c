/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:09:45 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/11 13:04:41 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <signal.h>

int	update_command(t_command *cmd)
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

static int	handle_fd(t_command_table *table,  t_command *cmd, char *file, char *arg)
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
		if (check_redir_in(file, 0) != 0)
			return (table->code = 1, 1);
		if (cmd->fd_in > 1)
			close(cmd->fd_in);
		cmd->fd_in = open(file, O_RDONLY, 0644);
	}
	return (0);
}

int	redir(t_command_table *table, t_command *cmd)
{
	int		i;

	i = 0;
	cmd->n_args = 0;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] == '>' || cmd->args[i][0] == '<')
		{
			if (handle_fd(table, cmd, cmd->args[i + 1], cmd->args[i]) == 1)
				return (table->code = 1, 1);
			i++;
		}
		else
			cmd->n_args++;
		i++;
	}
	return (0);
}

int	heredoc(t_command_table *table, t_command *cmd, char *temp)
{
	char	*deli;
	char	*line;
	char	*new_line;
	int		nb_line;
	int		diff;

	diff = temp[0] == '\'' || temp[0] == '"';
	deli = remove_quotes_pair(temp);
	if (malloc_assert(deli, __FILE__, __LINE__, __FUNCTION__))
		return (MALLOC_ERR);
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	cmd->fd_in = open("/tmp/temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_in == -1)
		return (perror("Failed to open file"), 1);
	nb_line = 0;
	while (1)
	{
		line = readline("> ");
		if (g_signal_received == SIGINT)
			return (free(deli), table->code = 130, 1);
		if (!line)
		{
			ft_dprintf(2, "%s%s %d delimited by end-of-file (wanted `%s')\n%s",
				ORANGE, "minishell: warning: here-document at line",
				nb_line, deli, RESET);
			break ;
		}
		else if (!ft_strcmp(line, deli))
		{
			free(line);
			break ;
		}
		else if (!diff && !g_signal_received)
		{
			new_line = process_var(line, table->env, table->code, NULL);
			free(line);
			if (new_line == NULL)
				return (1);
			line = new_line;
		}
		ft_putendl_fd(line, cmd->fd_in);
		free(line);
	}
	free(deli);
	close(cmd->fd_in);
	cmd->fd_in = open("/tmp/temp.txt", O_RDONLY, 0644);
	if (cmd->fd_in == -1)
		return (perror("Failed to open file"), 1);
	return (0);
}
