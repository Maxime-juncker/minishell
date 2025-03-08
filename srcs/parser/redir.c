/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:09:45 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/08 13:19:59 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <signal.h>

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

static int	handle_eof(char **line, char *deli, int diff, t_command *cmd)
{
	static int	nb_line = -1;
	char		*new_line;

	nb_line++;
	if (!line)
	{
		ft_dprintf(2, "%s%s %d delimited by end-of-file (wanted `%s')\n%s",
			ORANGE, "minishell: warning: here-document at line",
			nb_line, deli, RESET);
		nb_line = -1;
		return (1);
	}
	else if (!ft_strcmp(*line, deli))
		return (free(*line), nb_line = -1, 1);
	else if (!diff && !g_signal_received)
	{
		new_line = process_var(*line, cmd->env, cmd->code, NULL);
		free(*line);
		if (new_line == NULL)
			return (1);
		*line = new_line;
	}
	return (0);
}

static int	heredoc(t_command *cmd, char *deli, int diff)
{
	char	*line;

	cmd->fd_in = open("/tmp/temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_in == -1)
		return (perror("Failed to open file"), 1);
	while (1)
	{
		if (g_signal_received == SIGINT)
			return (1);
		line = readline("> ");
		if (!line && handle_eof(NULL, deli, 0, cmd))
			break ;
		if (handle_eof(&line, deli, diff, cmd))
			break ;
		ft_putendl_fd(line, cmd->fd_in);
		free(line);
	}
	close(cmd->fd_in);
	cmd->fd_in = open("/tmp/temp.txt", O_RDONLY, 0644);
	if (cmd->fd_in == -1)
		return (perror("Failed to open file"), 1);
	return (0);
}

static int	handle_fd(t_command *cmd, char *file, char *arg)
{
	char	*temp;

	temp = remove_quotes_pair(file);
	if (malloc_assert(temp, __FILE__, __LINE__, __FUNCTION__) == MALLOC_ERR)
		return (cmd->code = MALLOC_ERR, MALLOC_ERR);
	if (arg[0] == '>')
	{
		if (cmd->fd_out > 1)
			close(cmd->fd_out);
		if (arg[0] == arg[1])
			cmd->fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			cmd->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else
	{
		if (cmd->fd_in > 1)
			close(cmd->fd_in);
		if (arg[0] != arg[1])
			cmd->fd_in = open(file, O_RDONLY, 0644);
		else if (arg[0] == arg[1] && heredoc(cmd, temp, ft_strcmp(file, temp)))
			return (free(temp), 1);
	}
	return (free(temp), 0);
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
			if (handle_fd(cmd, cmd->args[i + 1], cmd->args[i]) == 1)
				return (1);
			if (cmd->code == MALLOC_ERR)
				return (MALLOC_ERR);
			if (cmd->fd_in == -1 || cmd->fd_out == -1)
				return (0);
			i++;
		}
		else
			cmd->n_args++;
		i++;
	}
	return (update_command(cmd));
}
