/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:09:45 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/01 22:03:21 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ls -l > 1 -a

#include "minishell.h"
#include <fcntl.h>
#include <readline/readline.h>

static int	update_command(t_command *cmd)
{
	char	**temp;
	int		i;
	int		j;

	temp = malloc(sizeof(char *) * (cmd->n_args + 1));
	if (malloc_assert(temp, __FILE__, __LINE__, __FUNCTION__) == MALLOC_ERR)
		return (MALLOC_ERR);
	i = 0;
	j = 0;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] != '>' && cmd->args[i][0] != '<')
			temp[j++] = cmd->args[i++];
		else
		{
			free(cmd->args[i]);
			free(cmd->args[i + 1]);
			i += 2;
		}
	}
	free(cmd->args);
	temp[j] = NULL;
	cmd->args = temp;
	return (0);
}

static int	handle_eof(char *line, char *deli, int nb)
{
	if (!line)
	{
		ft_dprintf(2, "%s%s %d delimited by end-of-file (wanted `%s')\n%s",
			ORANGE, "minishell: warning: here-document at line",
			nb, deli, RESET);
		return (1);
	}
	else if (!ft_strcmp(line, deli))
	{
		free(line);
		return (1);
	}
	return (0);
}

static int	heredoc(t_command *cmd, char *deli)
{
	char	*line;
	int		nb_line;

	cmd->fd_in = open("/tmp/temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_in == -1)
		return (perror("Failed to open file"), 1);
	nb_line = 0;
	while (1)
	{
		if (g_signal_received)
			return (g_signal_received = 0, 1);
		line = readline("> ");
		if (handle_eof(line, deli, nb_line++))
			break ;
		write(cmd->fd_in, line, ft_strlen(line));
		write(cmd->fd_in, "\n", 1);
	}
	close(cmd->fd_in);
	cmd->fd_in = open("/tmp/temp.txt", O_RDONLY, 0644);
	if (cmd->fd_in == -1)
		return (perror("Failed to open file"), 1);
	return (0);
}

static int	handle_fd(t_command *cmd, char *file, char c, int db_redir)
{
	if (c == '>')
	{
		if (cmd->fd_out > 1)
			close(cmd->fd_out);
		if (db_redir)
			cmd->fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			cmd->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else
	{
		if (cmd->fd_in > 1)
			close(cmd->fd_in);
		if (!db_redir)
			cmd->fd_in = open(file, O_RDONLY, 0644);
		else if (db_redir && heredoc(cmd, file))
			return (MALLOC_ERR);
	}
	return (0);
}

int	redir(t_command *cmd)
{
	int		i;

	i = 0;
	cmd->n_args = 0;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] == '>' || cmd->args[i][0] == '<')
		{
			handle_fd(cmd, cmd->args[i + 1], cmd->args[i][0],
				cmd->args[i][0] == cmd->args[i][1]);
			if (cmd->fd_in == -1 || cmd->fd_out == -1)
				return (perror("Failed to open file"), 1);
			i++;
		}
		else
			cmd->n_args++;
		i++;
	}
	return (update_command(cmd));
}
