/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:09:21 by abidolet          #+#    #+#             */
/*   Updated: 2025/02/25 16:07:28 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_eof(char *line, char *deli, int nb)
{
	if (!line)
	{
		ft_dprintf(2, "%s%s %d delimited by end-of-file (wanted `%s')\n%s",
			ORANGE, "\nminishell: warning: here-document at line",
			nb, deli, RESET);
		return (1);
	}
	else if (!ft_strncmp(line, deli, ft_strlen(line) - 1)
		&& ft_strlen(deli) == ft_strlen(line) - 1)
	{
		free(line);
		return (1);
	}
	return (0);
}

static char	*append_str(char *old, char *append_str, int new_len)
{
	char	*new_str;

	if (!old)
		return (ft_strdup(append_str));
	new_str = malloc(new_len);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, old, new_len);
	free(old);
	ft_strlcat(new_str, append_str, new_len);
	return (new_str);
}

int	heredoc(t_command *cmd, char *deli)
{
	char	*doc;
	char	*line;
	int		nb_line;

	cmd->fd_in = open("/tmp/temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	doc = NULL;
	nb_line = 0;
	while (1)
	{
		ft_putstr_fd("> ", 0);
		line = get_next_line(0);
		if (handle_eof(line, deli, nb_line))
			break ;
		nb_line++;
		doc = append_str(doc, line, ft_strlen(doc) + ft_strlen(line) + 1);
		free(line);
		if (!doc)
			return (1);
	}
	if (doc)
		write(cmd->fd_in, doc, ft_strlen(doc));
	close(cmd->fd_in);
	cmd->fd_in = open("/tmp/temp.txt", O_RDONLY, 0644);
	return (free(doc), 0);
}
