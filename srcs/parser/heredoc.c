/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:09:21 by abidolet          #+#    #+#             */
/*   Updated: 2025/02/21 15:09:52 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	heredoc(t_command *cmd, char *deli)
{
	char	*doc;
	char	*line;
	size_t	len;
	int		nb;

	cmd->fd_in = open("/tmp/temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	doc = NULL;
	nb = 0;
	while (1)
	{
		ft_putstr_fd("> ", 0);
		line = get_next_line(0);
		if (!line)
			ft_dprintf(2, "%s%d delimited by end-of-file (wanted `%s')\033[0m\n",
				"\n\033[38;5;208mminishell: warning: here-document at line ",
					nb, deli);
		len = ft_strlen(line) - 1;
		if (!line || (!ft_strncmp(line, deli, len) && ft_strlen(deli) == len))
		{
			if (line)
				free(line);
			break ;
		}
		nb++;
		doc = append_str(doc, line, ft_strlen(doc) + len + 2);
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
