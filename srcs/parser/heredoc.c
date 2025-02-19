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

static void	handle_eof(char **line, char *deli)
{
	if (!*line)
		printf("minishell: warning: %s (wanted `%s')\n",
			"here-document delimited by end-of-file", deli);
	else
		free(*line);
}

int	heredoc(t_command *cmd, char *deli)
{
	char	*doc;
	char	*line;
	size_t	len;

	cmd->fd_in = open("/tmp/temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	doc = NULL;
	while (1)
	{
		line = get_next_line(0);
		len = ft_strlen(line) - 1;
		if (!line || (!ft_strncmp(line, deli, len) && ft_strlen(deli) == len))
		{
			handle_eof(&line, deli);
			break ;
		}
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
