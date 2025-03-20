/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 21:46:10 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/20 16:39:15 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <signal.h>

void	print_heredoc_warning(char *deli, int nb_line)
{
	ft_dprintf(2, "%s%s %d delimited by end-of-file (wanted `%s')\n%s",
		ORANGE, "minishell: warning: here-document at line",
		nb_line, deli, RESET);
}

int	heredoc_loop(t_command_table *table, t_command *cmd, char *deli, int diff)
{
	char	*line;
	char	*new_line;
	int		nb_line;

	nb_line = 0;
	while (1)
	{
		line = readline("> ");
		if (g_signal_received == SIGINT)
			return (free(deli), table->code = 130, 1);
		if (!line)
			return (print_heredoc_warning(deli, nb_line), 0);
		else if (!ft_strcmp(line, deli))
			return (free(line), 0);
		else if (!diff && !g_signal_received)
		{
			new_line = process_var(line, table->env, table->code, NULL);
			free(line);
			if (!new_line)
				return (1);
			ft_putendl_fd(new_line, cmd->fd_in);
			free(new_line);
		}
		nb_line++;
	}
}

int	heredoc(t_command_table *table, t_command *cmd, char *temp)
{
	static int	fd = -1;
	char		*deli;
	int			diff;

	diff = temp[0] == '\'' || temp[0] == '"';
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (fd != -1)
		close(fd);
	cmd->fd_in = open("/tmp/temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_in == -1)
		return (perror("Failed to open file"), 1);
	deli = remove_quotes_pair(temp);
	if (malloc_assert(deli, __FILE__, __LINE__, __FUNCTION__))
		return (MALLOC_ERR);
	if (heredoc_loop(table, cmd, deli, diff) == 1)
		return (1);
	free(deli);
	close(cmd->fd_in);
	cmd->fd_in = open("/tmp/temp.txt", O_RDONLY, 0644);
	fd = cmd->fd_in;
	if (cmd->fd_in == -1)
		return (perror("Failed to open file"), 1);
	return (0);
}
