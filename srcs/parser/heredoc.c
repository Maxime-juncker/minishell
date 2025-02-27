/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:09:21 by abidolet          #+#    #+#             */
/*   Updated: 2025/02/27 15:32:34 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <signal.h>

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

static char	*append_str(char *old, char *append_str)
{
	int		new_len;
	char	*new_str;

	if (!old)
		return (append_str);
	new_len = ft_strlen(old) + ft_strlen(append_str) + 1;
	new_str = malloc(new_len);
	if (!new_str)
		return (free(old), free(append_str),
			malloc_assert(NULL, __FILE__, __LINE__, __FUNCTION__), NULL);
	ft_strlcpy(new_str, old, new_len);
	free(old);
	ft_strlcat(new_str, append_str, new_len);
	free(append_str);
	return (new_str);
}

int	heredoc(t_command *cmd, char *deli)
{
	char	*doc;
	char	*line;
	int		nb_line;
	char	*new_line;

	cmd->fd_in = open("/tmp/temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	doc = NULL;
	nb_line = 0;
	while (1)
	{
		if (g_signal_received == SIGINT)
			return (g_signal_received = 0, free(doc), 1);
		line = readline("> ");
		if (handle_eof(line, deli, nb_line++))
			break ;
		if (line)
			new_line = ft_charjoin(line, '\n');
		doc = append_str(doc, new_line);
		if (!doc)
			return (MALLOC_ERR);
	}
	if (doc)
		write(cmd->fd_in, doc, ft_strlen(doc));
	close(cmd->fd_in);
	return (cmd->fd_in = open("/tmp/temp.txt", O_RDONLY, 0644), free(doc), 0);
}
